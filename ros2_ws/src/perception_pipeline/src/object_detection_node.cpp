#include "perception_pipeline/object_detection_node.hpp"

namespace perception_pipeline {

ObjectDetectionNode::ObjectDetectionNode()
: Node("object_detection_node"),
  tf_buffer_(this->get_clock()),
  tf_listener_(tf_buffer_)
{
  // TODO: declare parameters (mask_b/g/r, tolerance, min/max_depth_m,
  //       dedup_radius_m, min_points)
  setup_interfaces();
}

void ObjectDetectionNode::setup_interfaces()
{
  // TODO: create semantic/depth/info subscribers and lantern_poses publisher
}

void ObjectDetectionNode::on_depth(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO: store latest depth image under data_mutex_
}

void ObjectDetectionNode::on_camera_info(
  const sensor_msgs::msg::CameraInfo::SharedPtr /*msg*/)
{
  // TODO: store camera info under data_mutex_
}

void ObjectDetectionNode::on_semantic(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO: detect target-colour pixels, back-project to 3D, deduplicate, publish
}

bool ObjectDetectionNode::is_unique(
  const geometry_msgs::msg::Point & /*p*/) const
{
  // TODO: return false if p is within dedup_radius_m_ of any existing detection
  return true;
}

void ObjectDetectionNode::publish_detection(
  const geometry_msgs::msg::Point & /*p*/)
{
  // TODO: append to detections_, build LanternPoseArray, publish
}

}  // namespace perception_pipeline

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<perception_pipeline::ObjectDetectionNode>());
  rclcpp::shutdown();
  return 0;
}
