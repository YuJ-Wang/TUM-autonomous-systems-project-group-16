#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

namespace perception_pipeline {

class SemanticCameraSubscriberNode : public rclcpp::Node {
public:
  SemanticCameraSubscriberNode();

private:
  void setup_interfaces();
  void on_semantic_image(const sensor_msgs::msg::Image::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr semantic_sub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr mask_pub_;

  int mask_b_{4};
  int mask_g_{235};
  int mask_r_{255};
  int tolerance_{10};
};

}  // namespace perception_pipeline
