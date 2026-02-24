#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

namespace perception_pipeline {

class DepthToPointcloudNode : public rclcpp::Node {
public:
  DepthToPointcloudNode();

private:
  void setup_interfaces();
  void on_camera_info(const sensor_msgs::msg::CameraInfo::SharedPtr msg);
  void on_mask(const sensor_msgs::msg::Image::SharedPtr msg);
  void on_depth_image(const sensor_msgs::msg::Image::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr info_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr mask_sub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_pub_;

  sensor_msgs::msg::CameraInfo::SharedPtr camera_info_;
  sensor_msgs::msg::Image::SharedPtr semantic_mask_;
  bool use_semantic_mask_{true};
  double min_depth_m_{0.1};
  double max_depth_m_{25.0};
};

}  // namespace perception_pipeline
