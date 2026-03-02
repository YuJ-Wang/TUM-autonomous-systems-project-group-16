#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/imgproc.hpp>
#include <sensor_msgs/image_encodings.hpp>

#include "perception_pipeline/semantic_camera_subscriber_node.hpp"

namespace perception_pipeline {

SemanticCameraSubscriberNode::SemanticCameraSubscriberNode()
: Node("semantic_camera_subscriber_node") {
  mask_b_ = this->declare_parameter<int>("mask_b", 4);
  mask_g_ = this->declare_parameter<int>("mask_g", 235);
  mask_r_ = this->declare_parameter<int>("mask_r", 255);
  tolerance_ = this->declare_parameter<int>("tolerance", 10);
  setup_interfaces();
}

void SemanticCameraSubscriberNode::setup_interfaces() {
  semantic_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/Quadrotor/Sensors/SemanticCamera/image_raw", rclcpp::SensorDataQoS(),
    std::bind(&SemanticCameraSubscriberNode::on_semantic_image, this, std::placeholders::_1));

  mask_pub_ = this->create_publisher<sensor_msgs::msg::Image>("/perception/semantic_mask", 10);
}

void SemanticCameraSubscriberNode::on_semantic_image(const sensor_msgs::msg::Image::SharedPtr msg) {
  try {
    auto cv_ptr = cv_bridge::toCvCopy(*msg, sensor_msgs::image_encodings::BGR8);

    cv::Mat mask;
    const cv::Scalar low(mask_b_ - tolerance_, mask_g_ - tolerance_, mask_r_ - tolerance_);
    const cv::Scalar high(mask_b_ + tolerance_, mask_g_ + tolerance_, mask_r_ + tolerance_);
    cv::inRange(cv_ptr->image, low, high, mask);

    sensor_msgs::msg::Image::SharedPtr out =
      cv_bridge::CvImage(msg->header, sensor_msgs::image_encodings::MONO8, mask).toImageMsg();
    mask_pub_->publish(*out);
  } catch (const cv_bridge::Exception & ex) {
    RCLCPP_WARN(this->get_logger(), "semantic mask conversion failed: %s", ex.what());
  }
}

}  // namespace perception_pipeline

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<perception_pipeline::SemanticCameraSubscriberNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
