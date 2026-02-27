#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/opencv.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>
#include <vector>
#include <memory>

namespace detection {

/**
 * @brief Represents a detected lantern with position tracking
 */
struct DetectedLantern {
    geometry_msgs::msg::Point position;
    int count;
    rclcpp::Time last_update;
};

/**
 * @brief Detects lanterns using semantic segmentation and depth fusion
 * 
 * This node synchronizes semantic camera and depth images, detects lantern pixels,
 * back-projects to 3D, and tracks lantern positions in world frame.
 */
class LanternDetectorNode : public rclcpp::Node
{
public:
    using SyncPolicy = message_filters::sync_policies::ApproximateTime<
        sensor_msgs::msg::Image, sensor_msgs::msg::Image>;

    LanternDetectorNode();
    ~LanternDetectorNode() = default;

private:
    // Callbacks
    void depth_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg);
    void sync_callback(const sensor_msgs::msg::Image::ConstSharedPtr& semantic_msg,
                      const sensor_msgs::msg::Image::ConstSharedPtr& depth_msg);

    // Processing
    geometry_msgs::msg::Point compute_3d_position(const cv::Mat& mask, 
                                                  const cv::Mat& depth,
                                                  const cv::Size& mask_size, 
                                                  const cv::Size& depth_size);
    void update_lanterns(const geometry_msgs::msg::Point& new_pos);
    void publish_lanterns();

    // ROS Interfaces
    message_filters::Subscriber<sensor_msgs::msg::Image> semantic_sub_;
    message_filters::Subscriber<sensor_msgs::msg::Image> depth_sub_;
    std::shared_ptr<message_filters::Synchronizer<SyncPolicy>> sync_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr depth_info_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr pose_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;

    // TF
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

    // Camera intrinsics
    double fx_, fy_, cx_, cy_;
    bool depth_info_received_ = false;

    // Parameters
    std::string semantic_topic_;
    std::string depth_topic_;
    std::string world_frame_;
    double distance_threshold_;
    double min_depth_;
    double max_depth_;

    // Detected lanterns
    std::vector<DetectedLantern> lanterns_;
};

}  // namespace detection
