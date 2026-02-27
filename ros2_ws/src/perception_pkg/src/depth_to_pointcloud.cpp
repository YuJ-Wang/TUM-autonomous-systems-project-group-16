#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class DepthToPointCloudNode : public rclcpp::Node
{
public:
    DepthToPointCloudNode() : Node("depth_to_pointcloud")
    {
        // Declare parameters
        this->declare_parameter("depth_topic", "/realsense/depth/image");
        this->declare_parameter("camera_info_topic", "/realsense/depth/camera_info");
        this->declare_parameter("output_topic", "/camera/depth/points");
        this->declare_parameter("max_depth", 10.0);
        this->declare_parameter("downsample_factor", 1);

        // Get parameters
        std::string depth_topic = this->get_parameter("depth_topic").as_string();
        std::string info_topic = this->get_parameter("camera_info_topic").as_string();
        std::string output_topic = this->get_parameter("output_topic").as_string();
        max_depth_ = this->get_parameter("max_depth").as_double();
        downsample_factor_ = this->get_parameter("downsample_factor").as_int();

        // Subscribers
        depth_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            depth_topic, 10,
            std::bind(&DepthToPointCloudNode::depthCallback, this, std::placeholders::_1));

        info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
            info_topic, 10,
            std::bind(&DepthToPointCloudNode::infoCallback, this, std::placeholders::_1));

        pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/true_pose", 10,
            std::bind(&DepthToPointCloudNode::poseCallback, this, std::placeholders::_1));

        // Publisher
        pointcloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(output_topic, 10);

        RCLCPP_INFO(this->get_logger(), "Depth to PointCloud conversion node started (C++)");
        RCLCPP_INFO(this->get_logger(), "Subscribing to depth image: %s", depth_topic.c_str());
        RCLCPP_INFO(this->get_logger(), "Subscribing to camera info: %s", info_topic.c_str());
        RCLCPP_INFO(this->get_logger(), "Publishing point cloud: %s", output_topic.c_str());
        RCLCPP_INFO(this->get_logger(), "Downsample factor: %d", downsample_factor_);
    }

private:
    void infoCallback(const sensor_msgs::msg::CameraInfo::SharedPtr msg)
    {
        if (!camera_info_received_) {
            fx_ = msg->k[0];
            fy_ = msg->k[4];
            cx_ = msg->k[2];
            cy_ = msg->k[5];
            camera_info_received_ = true;
            RCLCPP_INFO(this->get_logger(), "Received camera info - fx: %.2f, fy: %.2f, cx: %.2f, cy: %.2f",
                       fx_, fy_, cx_, cy_);
        }
    }

    void poseCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
    {
        current_pose_ = msg;
        if (!pose_received_) {
            RCLCPP_INFO(this->get_logger(), "Received first pose data");
            pose_received_ = true;
        }
    }

    void depthCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        if (!camera_info_received_) {
            RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                               "Waiting for camera info...");
            return;
        }

        try {
            // Convert depth image
            cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, "16UC1");
            
            // Create point cloud message
            auto cloud_msg = std::make_shared<sensor_msgs::msg::PointCloud2>();
            cloud_msg->header = msg->header;
            cloud_msg->header.frame_id = msg->header.frame_id; // Use camera coordinate frame
            
            // Set point cloud fields
            sensor_msgs::PointCloud2Modifier modifier(*cloud_msg);
            modifier.setPointCloud2FieldsByString(1, "xyz");
            
            // Calculate point cloud
            std::vector<Eigen::Vector3f> points;
            depthToPoints(cv_ptr->image, points);
            
            // Populate point cloud data
            modifier.resize(points.size());
            sensor_msgs::PointCloud2Iterator<float> iter_x(*cloud_msg, "x");
            sensor_msgs::PointCloud2Iterator<float> iter_y(*cloud_msg, "y");
            sensor_msgs::PointCloud2Iterator<float> iter_z(*cloud_msg, "z");
            
            for (const auto& point : points) {
                *iter_x = point.x();
                *iter_y = point.y();
                *iter_z = point.z();
                ++iter_x;
                ++iter_y;
                ++iter_z;
            }
            
            pointcloud_pub_->publish(*cloud_msg);
            
        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Error processing depth image: %s", e.what());
        }
    }

    void depthToPoints(const cv::Mat& depth_image, std::vector<Eigen::Vector3f>& points)
    {
        points.clear();
        int height = depth_image.rows;
        int width = depth_image.cols;
        
        // Downsample processing
        for (int v = 0; v < height; v += downsample_factor_) {
            for (int u = 0; u < width; u += downsample_factor_) {
                uint16_t depth_value = depth_image.at<uint16_t>(v, u);
                float z = depth_value / 1000.0f; // Convert to meters
                
                // Filter invalid depth (only exclude zero/invalid depths)
                if (z > 0.0f && z <= max_depth_) {
                    // Pinhole camera model: back-project to 3D space
                    float x = (u - cx_) * z / fx_;
                    float y = (v - cy_) * z / fy_;
                    
                    points.emplace_back(x, y, z);
                }
            }
        }
    }

    // Subscribers
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    
    // Publisher
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_pub_;
    
    // Camera parameters
    double fx_, fy_, cx_, cy_;
    bool camera_info_received_ = false;
    
    // Pose
    geometry_msgs::msg::PoseStamped::SharedPtr current_pose_;
    bool pose_received_ = false;
    
    // Parameters
    double max_depth_;
    int downsample_factor_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DepthToPointCloudNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
