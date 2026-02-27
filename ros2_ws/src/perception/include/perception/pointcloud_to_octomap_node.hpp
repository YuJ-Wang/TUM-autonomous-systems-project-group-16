#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <octomap_msgs/msg/octomap.hpp>
#include <octomap/OcTree.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <memory>

namespace perception {

/**
 * @brief Builds a 3D octree map from point cloud data
 * 
 * This node subscribes to point clouds, performs raycasting to mark free/occupied
 * space, and publishes incremental OctoMap for navigation and visualization.
 */
class PointCloudToOctomapNode : public rclcpp::Node
{
public:
    PointCloudToOctomapNode();
    ~PointCloudToOctomapNode() = default;

private:
    // Callbacks
    void pointcloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    void pose_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg);

    // Publishing
    void publish_octomap();
    void publish_markers();

    // ROS Interfaces
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    rclcpp::Publisher<octomap_msgs::msg::Octomap>::SharedPtr octomap_pub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
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

}  // namespace perception
