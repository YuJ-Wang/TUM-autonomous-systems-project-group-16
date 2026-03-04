#pragma once

#include <mutex>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include "utils/msg/lantern_pose_array.hpp"

namespace perception_pipeline {

class ObjectDetectionNode : public rclcpp::Node {
public:
  ObjectDetectionNode();

private:
  void setup_interfaces();
  void on_depth(const sensor_msgs::msg::Image::SharedPtr msg);
  void on_camera_info(const sensor_msgs::msg::CameraInfo::SharedPtr msg);
  void on_semantic(const sensor_msgs::msg::Image::SharedPtr msg);
  bool is_unique(const geometry_msgs::msg::Point & p) const;
  void publish_detection(const geometry_msgs::msg::Point & p);

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr semantic_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_sub_;
  rclcpp::Publisher<utils::msg::LanternPoseArray>::SharedPtr lantern_pub_;

  std::mutex data_mutex_;
  sensor_msgs::msg::Image::SharedPtr latest_depth_;
  sensor_msgs::msg::CameraInfo::SharedPtr latest_info_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;

  int mask_b_{4};
  int mask_g_{235};
  int mask_r_{255};
  int tolerance_{10};
  double min_depth_m_{0.1};
  double max_depth_m_{25.0};
  double dedup_radius_m_{8.0};
  int min_points_{20};
  std::vector<geometry_msgs::msg::Point> detections_;
};

}  // namespace perception_pipeline
