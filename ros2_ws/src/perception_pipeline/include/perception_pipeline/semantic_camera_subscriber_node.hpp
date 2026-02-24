#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

namespace perception_pipeline {

class SemanticCameraSubscriberNode : public rclcpp::Node {
public:
  SemanticCameraSubscriberNode();

private:
  void setup_interfaces();
  void on_image(const sensor_msgs::msg::Image::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
};

}  // namespace perception_pipeline
