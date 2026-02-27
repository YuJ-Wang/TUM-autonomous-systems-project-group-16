#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>

namespace perception {

/**
 * @brief Converts depth images to 3D point clouds using pinhole camera model
 * 
 * This node subscribes to depth images and camera info, performs back-projection
 * to generate 3D point clouds in the camera frame.
 */
class DepthToPointCloudNode : public rclcpp::Node
{
public:
    DepthToPointCloudNode();
    ~DepthToPointCloudNode() = default;

private:
    // Callbacks
    void depth_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg);
    void pose_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg);

    // Processing
    void depth_to_points(const cv::Mat& depth_image, std::vector<Eigen::Vector3f>& points);

    // ROS Interfaces
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr camera_info_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_pub_;

    // Camera intrinsics
    double fx_, fy_, cx_, cy_;
    bool camera_info_received_ = false;

    // Pose tracking
    geometry_msgs::msg::PoseStamped::SharedPtr current_pose_;
    bool pose_received_ = false;

    // Parameters
    double max_depth_;
    int downsample_factor_;
};

}  // namespace perception
