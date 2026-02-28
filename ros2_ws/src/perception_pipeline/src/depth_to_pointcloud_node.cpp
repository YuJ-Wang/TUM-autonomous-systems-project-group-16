#include "perception_pipeline/depth_to_pointcloud_node.hpp"

namespace perception_pipeline {

DepthToPointcloudNode::DepthToPointcloudNode()
: Node("depth_to_pointcloud_node")
{
  // TODO: declare parameters (use_semantic_mask, min_depth_m, max_depth_m)
  setup_interfaces();
}

void DepthToPointcloudNode::setup_interfaces()
{
  // TODO: create depth/info/mask subscribers and cloud publisher
}

void DepthToPointcloudNode::on_camera_info(
  const sensor_msgs::msg::CameraInfo::SharedPtr /*msg*/)
{
  // TODO: store camera intrinsics
}

void DepthToPointcloudNode::on_mask(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO: store latest semantic mask
}

void DepthToPointcloudNode::on_depth_image(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO: back-project depth pixels to 3D, filter by mask, publish PointCloud2
}

}  // namespace perception_pipeline

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<perception_pipeline::DepthToPointcloudNode>());
  rclcpp::shutdown();
  return 0;
}
