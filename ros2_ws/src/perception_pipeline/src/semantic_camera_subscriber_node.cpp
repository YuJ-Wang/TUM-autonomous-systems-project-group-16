#include "perception_pipeline/semantic_camera_subscriber_node.hpp"

namespace perception_pipeline {

SemanticCameraSubscriberNode::SemanticCameraSubscriberNode()
: Node("semantic_camera_subscriber_node")
{
  // TODO: declare parameters
  setup_interfaces();
}

void SemanticCameraSubscriberNode::setup_interfaces()
{
  // TODO: create image subscriber and publisher
}

void SemanticCameraSubscriberNode::on_image(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO
}

}  // namespace perception_pipeline

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<perception_pipeline::SemanticCameraSubscriberNode>());
  rclcpp::shutdown();
  return 0;
}
