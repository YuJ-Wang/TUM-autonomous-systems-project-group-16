#include "mapping/voxel_grid_mapper_node.hpp"

namespace mapping {

VoxelGridMapperNode::VoxelGridMapperNode()
: Node("voxel_grid_mapper_node"),
  tf_buffer_(this->get_clock()),
  tf_listener_(tf_buffer_)
{
  // TODO: declare parameters
  setup_interfaces();
}

void VoxelGridMapperNode::setup_interfaces()
{
  // TODO: create subscriptions, publishers, and timer
}

void VoxelGridMapperNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr /*msg*/)
{
  // TODO
}

void VoxelGridMapperNode::on_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr /*msg*/)
{
  // TODO
}

void VoxelGridMapperNode::publish_map_summary()
{
  // TODO
}

std::optional<VoxelGridMapperNode::VoxelCoord> VoxelGridMapperNode::find_frontier_voxel() const
{
  // TODO
  return std::nullopt;
}

geometry_msgs::msg::Point VoxelGridMapperNode::voxel_to_world_center(
  const VoxelCoord & /*voxel*/) const
{
  // TODO
  return geometry_msgs::msg::Point{};
}

VoxelGridMapperNode::VoxelCoord VoxelGridMapperNode::world_to_voxel(
  double /*x*/, double /*y*/, double /*z*/) const
{
  // TODO
  return VoxelCoord{};
}

void VoxelGridMapperNode::mark_free_ray(
  const VoxelCoord & /*from*/, const VoxelCoord & /*to*/)
{
  // TODO
}

}  // namespace mapping

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<mapping::VoxelGridMapperNode>());
  rclcpp::shutdown();
  return 0;
}
