#include "perception/depth_to_pointcloud_node.hpp"

namespace perception {

DepthToPointCloudNode::DepthToPointCloudNode() 
    : Node("depth_to_pointcloud")
{
    // Declare parameters
    this->declare_parameter("depth_topic", "/realsense/depth/image");
    this->declare_parameter("camera_info_topic", "/realsense/depth/camera_info");
    this->declare_parameter("output_topic", "/camera/depth/points");
    this->declare_parameter("max_depth", 10.0);
    this->declare_parameter("downsample_factor", 1);

    // Get parameters
    std::string depth_topic = this->get_parameter("depth_topic").as_string();
    std::string camera_info_topic = this->get_parameter("camera_info_topic").as_string();
    std::string output_topic = this->get_parameter("output_topic").as_string();
    max_depth_ = this->get_parameter("max_depth").as_double();
    downsample_factor_ = this->get_parameter("downsample_factor").as_int();

    // Subscribers
    depth_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        depth_topic, 10,
        std::bind(&DepthToPointCloudNode::depth_callback, this, std::placeholders::_1));

    camera_info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
        camera_info_topic, 10,
        std::bind(&DepthToPointCloudNode::camera_info_callback, this, std::placeholders::_1));

    pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        "/true_pose", 10,
        std::bind(&DepthToPointCloudNode::pose_callback, this, std::placeholders::_1));

    // Publisher
    pointcloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(output_topic, 10);

    RCLCPP_INFO(this->get_logger(), "Depth to PointCloud conversion node started");
    RCLCPP_INFO(this->get_logger(), "  Depth topic: %s", depth_topic.c_str());
    RCLCPP_INFO(this->get_logger(), "  Camera info: %s", camera_info_topic.c_str());
    RCLCPP_INFO(this->get_logger(), "  Output topic: %s", output_topic.c_str());
    RCLCPP_INFO(this->get_logger(), "  Max depth: %.1f m", max_depth_);
    RCLCPP_INFO(this->get_logger(), "  Downsample factor: %d", downsample_factor_);
}

void DepthToPointCloudNode::camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg)
{
    if (!camera_info_received_) {
        fx_ = msg->k[0];
        fy_ = msg->k[4];
        cx_ = msg->k[2];
        cy_ = msg->k[5];
        camera_info_received_ = true;
        
        RCLCPP_INFO(this->get_logger(), "Camera intrinsics received:");
        RCLCPP_INFO(this->get_logger(), "  fx=%.2f fy=%.2f cx=%.2f cy=%.2f", fx_, fy_, cx_, cy_);
    }
}

void DepthToPointCloudNode::pose_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
    current_pose_ = msg;
    if (!pose_received_) {
        RCLCPP_INFO(this->get_logger(), "Pose data received");
        pose_received_ = true;
    }
}

void DepthToPointCloudNode::depth_callback(const sensor_msgs::msg::Image::SharedPtr msg)
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
        cloud_msg->header.frame_id = msg->header.frame_id;
        
        // Set point cloud fields
        sensor_msgs::PointCloud2Modifier modifier(*cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        
        // Calculate point cloud
        std::vector<Eigen::Vector3f> points;
        depth_to_points(cv_ptr->image, points);
        
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

void DepthToPointCloudNode::depth_to_points(const cv::Mat& depth_image, 
                                            std::vector<Eigen::Vector3f>& points)
{
    points.clear();
    const int height = depth_image.rows;
    const int width = depth_image.cols;
    
    // Reserve approximate size
    points.reserve((height * width) / (downsample_factor_ * downsample_factor_));
    
    // Process with downsampling
    for (int v = 0; v < height; v += downsample_factor_) {
        for (int u = 0; u < width; u += downsample_factor_) {
            const uint16_t depth_value = depth_image.at<uint16_t>(v, u);
            const float z = depth_value / 1000.0f;  // Convert mm to meters
            
            // Filter invalid depths
            if (z > 0.0f && z <= max_depth_) {
                // Pinhole camera model: back-project to 3D
                const float x = (u - cx_) * z / fx_;
                const float y = (v - cy_) * z / fy_;
                
                points.emplace_back(x, y, z);
            }
        }
    }
}

}  // namespace perception
