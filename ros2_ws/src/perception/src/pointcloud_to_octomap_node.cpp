#include "perception/pointcloud_to_octomap_node.hpp"
#include <octomap_msgs/conversions.h>
#include <std_msgs/msg/color_rgba.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace perception {

PointCloudToOctomapNode::PointCloudToOctomapNode()
    : Node("pointcloud_to_octomap")
{
    // Declare parameters
    this->declare_parameter("pointcloud_topic", "/camera/depth/points");
    this->declare_parameter("output_topic", "/octomap");
    this->declare_parameter("resolution", 0.15);
    this->declare_parameter("max_range", 100.0);
    this->declare_parameter("publish_rate", 1.0);
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
    octree_->setProbHit(0.65);
    octree_->setProbMiss(0.2);
    octree_->setClampingThresMin(0.12);
    octree_->setClampingThresMax(0.97);
    octree_->setOccupancyThres(0.5);

    // TF2 setup
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    // Subscribers
    pointcloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        pointcloud_topic, 10,
        std::bind(&PointCloudToOctomapNode::pointcloud_callback, this, std::placeholders::_1));

    pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        "/true_pose", 10,
        std::bind(&PointCloudToOctomapNode::pose_callback, this, std::placeholders::_1));

    // Publishers
    octomap_pub_ = this->create_publisher<octomap_msgs::msg::Octomap>(output_topic, 10);
    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("/octomap_markers", 10);

    // Timer
    publish_timer_ = this->create_wall_timer(
        std::chrono::duration<double>(1.0 / publish_rate),
        std::bind(&PointCloudToOctomapNode::publish_octomap, this));

    RCLCPP_INFO(this->get_logger(), "PointCloud to OctoMap node started");
    RCLCPP_INFO(this->get_logger(), "  Point cloud topic: %s", pointcloud_topic.c_str());
    RCLCPP_INFO(this->get_logger(), "  Output topic: %s", output_topic.c_str());
    RCLCPP_INFO(this->get_logger(), "  Resolution: %.3f m", resolution);
    RCLCPP_INFO(this->get_logger(), "  Max range: %.1f m", max_range_);
}

void PointCloudToOctomapNode::pose_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
    current_pose_ = msg;
    if (!pose_received_) {
        RCLCPP_INFO(this->get_logger(), "Pose data received");
        pose_received_ = true;
    }
}

void PointCloudToOctomapNode::pointcloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    if (!pose_received_) {
        RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                           "Waiting for pose data...");
        return;
    }

    geometry_msgs::msg::TransformStamped transform;
    try {
        transform = tf_buffer_->lookupTransform(
            frame_id_, msg->header.frame_id,
            msg->header.stamp, rclcpp::Duration::from_seconds(0.1));
    } catch (tf2::TransformException &ex) {
        RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                           "Transform failed: %s", ex.what());
        return;
    }

    octomap::point3d sensor_origin(
        transform.transform.translation.x,
        transform.transform.translation.y,
        transform.transform.translation.z);

    sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x");
    sensor_msgs::PointCloud2ConstIterator<float> iter_y(*msg, "y");
    sensor_msgs::PointCloud2ConstIterator<float> iter_z(*msg, "z");

    // Clear the octree for real-time update (no historical records)
    octree_->clear();
    
    size_t point_counter = 0;

    for (; iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z) {
        geometry_msgs::msg::PointStamped point_in, point_out;
        point_in.header = msg->header;
        point_in.point.x = *iter_x;
        point_in.point.y = *iter_y;
        point_in.point.z = *iter_z;

        tf2::doTransform(point_in, point_out, transform);

        double range = std::sqrt(
            std::pow(point_out.point.x - sensor_origin.x(), 2) +
            std::pow(point_out.point.y - sensor_origin.y(), 2) +
            std::pow(point_out.point.z - sensor_origin.z(), 2));

        if (range <= max_range_ && range > 0.1) {
            octomap::point3d point(point_out.point.x, point_out.point.y, point_out.point.z);
            octree_->updateNode(point, true);
            point_counter++;
        }
    }

    octree_->updateInnerOccupancy();
    octree_->prune();

    if (point_counter > 0) {
        point_count_ = point_counter;
        update_count_++;

        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 5000,
                           "Current frame: %zu occupied voxels", point_counter);
    }
}

void PointCloudToOctomapNode::publish_octomap()
{
    if (update_count_ == 0) return;
    
    octomap_msgs::msg::Octomap map_msg;
    map_msg.header.stamp = this->now();
    map_msg.header.frame_id = frame_id_;

    if (octomap_msgs::fullMapToMsg(*octree_, map_msg)) {
        octomap_pub_->publish(map_msg);
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 10000,
                           "Published real-time OctoMap (%zu nodes)", octree_->size());
    }

    publish_markers();
}

void PointCloudToOctomapNode::publish_markers()
{
    visualization_msgs::msg::MarkerArray marker_array;

    visualization_msgs::msg::Marker delete_marker;
    delete_marker.header.frame_id = frame_id_;
    delete_marker.header.stamp = this->now();
    delete_marker.ns = "octomap";
    delete_marker.id = 0;
    delete_marker.action = visualization_msgs::msg::Marker::DELETEALL;
    marker_array.markers.push_back(delete_marker);

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

    for (auto it = octree_->begin_leafs(); it != octree_->end_leafs(); ++it) {
        if (octree_->isNodeOccupied(*it)) {
            geometry_msgs::msg::Point point;
            point.x = it.getX();
            point.y = it.getY();
            point.z = it.getZ();
            marker.points.push_back(point);

            std_msgs::msg::ColorRGBA color;
            float height_ratio = (point.z + 2.0) / 4.0;
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
    }
}

}  // namespace perception
