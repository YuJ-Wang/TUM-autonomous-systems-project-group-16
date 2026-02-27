#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <octomap_msgs/msg/octomap.hpp>
#include <octomap_msgs/conversions.h>
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <std_msgs/msg/color_rgba.hpp>

class PointCloudToOctomapNode : public rclcpp::Node
{
public:
    PointCloudToOctomapNode() : Node("pointcloud_to_octomap")
    {
        // Declare parameters
        this->declare_parameter("pointcloud_topic", "/camera/depth/points");
        this->declare_parameter("output_topic", "/octomap");
        this->declare_parameter("resolution", 0.1);  // 10cm resolution
        this->declare_parameter("max_range", 8.0);
        this->declare_parameter("publish_rate", 1.0);  // Publish map every 1 second
        this->declare_parameter("frame_id", "world");

        // Get parameters
        std::string pointcloud_topic = this->get_parameter("pointcloud_topic").as_string();
        std::string output_topic = this->get_parameter("output_topic").as_string();
        double resolution = this->get_parameter("resolution").as_double();
        max_range_ = this->get_parameter("max_range").as_double();
        double publish_rate = this->get_parameter("publish_rate").as_double();
        frame_id_ = this->get_parameter("frame_id").as_string();

        // Initialize OctoMap
        octree_ = std::make_shared<octomap::OcTree>(resolution);
        // VERY aggressive clearing for dynamic environments
        octree_->setProbHit(0.65);   // Moderate increase when occupied
        octree_->setProbMiss(0.2);   // VERY aggressive decrease when free
        octree_->setClampingThresMin(0.12);
        octree_->setClampingThresMax(0.97);
        octree_->setOccupancyThres(0.5);  // Threshold for occupied vs free

        // TF2 setup
        tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        // Subscribers
        pointcloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            pointcloud_topic, 10,
            std::bind(&PointCloudToOctomapNode::pointcloudCallback, this, std::placeholders::_1));

        pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/true_pose", 10,
            std::bind(&PointCloudToOctomapNode::poseCallback, this, std::placeholders::_1));

        // Publisher
        octomap_pub_ = this->create_publisher<octomap_msgs::msg::Octomap>(output_topic, 10);
        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("/octomap_markers", 10);

        // Timer for periodic publishing
        publish_timer_ = this->create_wall_timer(
            std::chrono::duration<double>(1.0 / publish_rate),
            std::bind(&PointCloudToOctomapNode::publishOctomap, this));

        RCLCPP_INFO(this->get_logger(), "PointCloud to OctoMap node started");
        RCLCPP_INFO(this->get_logger(), "Subscribing to point cloud: %s", pointcloud_topic.c_str());
        RCLCPP_INFO(this->get_logger(), "Publishing OctoMap: %s", output_topic.c_str());
        RCLCPP_INFO(this->get_logger(), "Resolution: %.3f m, Max range: %.1f m", resolution, max_range_);
    }

private:
    void poseCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
    {
        current_pose_ = msg;
        if (!pose_received_) {
            RCLCPP_INFO(this->get_logger(), "Received first pose data");
            pose_received_ = true;
        }
    }

    void pointcloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        if (!pose_received_) {
            RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                               "Waiting for pose data...");
            return;
        }

        // Get transform from camera frame to world frame
        geometry_msgs::msg::TransformStamped transform;
        try {
            transform = tf_buffer_->lookupTransform(
                frame_id_, msg->header.frame_id, 
                msg->header.stamp, rclcpp::Duration::from_seconds(0.1));
        } catch (tf2::TransformException &ex) {
            RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                               "Could not transform from %s to %s: %s",
                               msg->header.frame_id.c_str(), frame_id_.c_str(), ex.what());
            return;
        }

        // Get sensor origin in world frame
        octomap::point3d sensor_origin(
            transform.transform.translation.x,
            transform.transform.translation.y,
            transform.transform.translation.z
        );

        // Process point cloud
        sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x");
        sensor_msgs::PointCloud2ConstIterator<float> iter_y(*msg, "y");
        sensor_msgs::PointCloud2ConstIterator<float> iter_z(*msg, "z");

        octomap::Pointcloud octomap_cloud;
        
        for (; iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z) {
            // Transform point to world frame
            geometry_msgs::msg::PointStamped point_in, point_out;
            point_in.header = msg->header;
            point_in.point.x = *iter_x;
            point_in.point.y = *iter_y;
            point_in.point.z = *iter_z;

            tf2::doTransform(point_in, point_out, transform);

            // Filter by range
            double range = std::sqrt(
                std::pow(point_out.point.x - sensor_origin.x(), 2) +
                std::pow(point_out.point.y - sensor_origin.y(), 2) +
                std::pow(point_out.point.z - sensor_origin.z(), 2)
            );

            if (range <= max_range_ && range > 0.1) {
                octomap_cloud.push_back(
                    point_out.point.x,
                    point_out.point.y,
                    point_out.point.z
                );
            }
        }

        // Insert point cloud into octree with raycasting to mark free space
        if (octomap_cloud.size() > 0) {
            // insertPointCloud with raycasting: marks rays as free, endpoints as occupied
            // lazy_eval=false: update immediately, discretize=true: enable raycasting
            octree_->insertPointCloud(octomap_cloud, sensor_origin, max_range_, false, true);
            
            // Also manually mark far free space if no points detected at max range
            // This helps clear voxels when objects move away
            if (octomap_cloud.size() < 1000) {  // If sparse point cloud, likely open space
                // Insert some free space samples at max range in viewing direction
                for (double angle_h = -0.3; angle_h <= 0.3; angle_h += 0.15) {
                    for (double angle_v = -0.2; angle_v <= 0.2; angle_v += 0.15) {
                        octomap::point3d ray_end(
                            sensor_origin.x() + max_range_ * std::cos(angle_v) * std::cos(angle_h),
                            sensor_origin.y() + max_range_ * std::cos(angle_v) * std::sin(angle_h),
                            sensor_origin.z() + max_range_ * std::sin(angle_v)
                        );
                        octree_->insertRay(sensor_origin, ray_end, max_range_);
                    }
                }
            }
            
            point_count_ += octomap_cloud.size();
            update_count_++;

            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 5000,
                               "Inserted %zu points, Total updates: %d, Total points: %ld",
                               octomap_cloud.size(), update_count_, point_count_);
        }
    }

    void publishOctomap()
    {
        if (update_count_ == 0) {
            return;  // No data yet
        }

        // Prune tree to remove uncertain voxels (below occupancy threshold)
        // This actively removes voxels that have been observed as free
        octree_->prune();
        
        // Update inner occupancy
        octree_->updateInnerOccupancy();

        // Convert to message
        octomap_msgs::msg::Octomap map_msg;
        map_msg.header.stamp = this->now();
        map_msg.header.frame_id = frame_id_;
        
        if (octomap_msgs::fullMapToMsg(*octree_, map_msg)) {
            octomap_pub_->publish(map_msg);
            
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 10000,
                               "Published OctoMap with %zu nodes", 
                               octree_->size());
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to serialize OctoMap");
        }

        // Also publish as MarkerArray for better RViz2 compatibility
        publishMarkers();
    }

    void publishMarkers()
    {
        visualization_msgs::msg::MarkerArray marker_array;
        
        // Delete old markers
        visualization_msgs::msg::Marker delete_marker;
        delete_marker.header.frame_id = frame_id_;
        delete_marker.header.stamp = this->now();
        delete_marker.ns = "octomap";
        delete_marker.id = 0;
        delete_marker.action = visualization_msgs::msg::Marker::DELETEALL;
        marker_array.markers.push_back(delete_marker);
        
        // Create cube list marker for occupied voxels
        visualization_msgs::msg::Marker marker;
        marker.header.frame_id = frame_id_;
        marker.header.stamp = this->now();
        marker.ns = "octomap";
        marker.id = 1;
        marker.type = visualization_msgs::msg::Marker::CUBE_LIST;
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.scale.x = octree_->getResolution();
        marker.scale.y = octree_->getResolution();
        marker.scale.z = octree_->getResolution();
        marker.color.a = 0.8;
        marker.pose.orientation.w = 1.0;
        
        // Iterate through occupied voxels
        for (auto it = octree_->begin_leafs(); it != octree_->end_leafs(); ++it) {
            if (octree_->isNodeOccupied(*it)) {
                geometry_msgs::msg::Point point;
                point.x = it.getX();
                point.y = it.getY();
                point.z = it.getZ();
                marker.points.push_back(point);
                
                // Color based on height (z-axis)
                std_msgs::msg::ColorRGBA color;
                float height_ratio = (point.z + 2.0) / 4.0;  // Normalize height
                color.r = height_ratio;
                color.g = 1.0 - height_ratio;
                color.b = 0.5;
                color.a = 0.8;
                marker.colors.push_back(color);
            }
        }
        
        if (!marker.points.empty()) {
            marker_array.markers.push_back(marker);
            marker_pub_->publish(marker_array);
            
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 10000,
                               "Published %zu occupied voxels as markers", 
                               marker.points.size());
        }
    }

    // Subscribers
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    
    // Publisher
    rclcpp::Publisher<octomap_msgs::msg::Octomap>::SharedPtr octomap_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
    
    // Timer
    rclcpp::TimerBase::SharedPtr publish_timer_;
    
    // TF2
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    
    // OctoMap
    std::shared_ptr<octomap::OcTree> octree_;
    
    // State
    geometry_msgs::msg::PoseStamped::SharedPtr current_pose_;
    bool pose_received_ = false;
    int update_count_ = 0;
    long point_count_ = 0;
    
    // Parameters
    double max_range_;
    std::string frame_id_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PointCloudToOctomapNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
