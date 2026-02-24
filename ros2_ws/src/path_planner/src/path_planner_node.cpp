#include "path_planner/path_planner_node.hpp"

namespace path_planner {

PathPlannerNode::PathPlannerNode()
: Node("path_planner_node")
{
  // TODO: declare parameters
  setup_interfaces();
}

void PathPlannerNode::setup_interfaces()
{
  // TODO: create subscriptions and publishers
}

void PathPlannerNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr /*msg*/)
{
  // TODO
}

void PathPlannerNode::on_goal(const geometry_msgs::msg::PoseStamped::SharedPtr /*msg*/)
{
  // TODO
}

void PathPlannerNode::on_frontier_goal(const geometry_msgs::msg::Point::SharedPtr /*msg*/)
{
  // TODO
}

void PathPlannerNode::on_global_map(const utils::msg::GlobalMap::SharedPtr /*msg*/)
{
  // TODO
}

int64_t PathPlannerNode::pack_key(int /*x*/, int /*y*/, int /*z*/)
{
  // TODO
  return 0;
}

PathPlannerNode::VoxelCoord PathPlannerNode::unpack_key(int64_t /*key*/)
{
  // TODO
  return VoxelCoord{};
}

PathPlannerNode::VoxelCoord PathPlannerNode::world_to_voxel(
  const geometry_msgs::msg::Point & /*p*/) const
{
  // TODO
  return VoxelCoord{};
}

geometry_msgs::msg::Point PathPlannerNode::voxel_to_world_center(
  const VoxelCoord & /*v*/) const
{
  // TODO
  return geometry_msgs::msg::Point{};
}

bool PathPlannerNode::is_occupied(const VoxelCoord & /*voxel*/) const
{
  // TODO
  return false;
}

std::optional<PathPlannerNode::VoxelCoord> PathPlannerNode::find_nearest_free(
  const VoxelCoord & /*start*/, int /*max_radius*/) const
{
  // TODO
  return std::nullopt;
}

std::vector<PathPlannerNode::VoxelCoord> PathPlannerNode::run_astar(
  const VoxelCoord & /*start*/, const VoxelCoord & /*goal*/) const
{
  // TODO
  return {};
}

nav_msgs::msg::Path PathPlannerNode::build_straight_line_path(
  const geometry_msgs::msg::PoseStamped & /*goal*/) const
{
  // TODO
  return nav_msgs::msg::Path{};
}

void PathPlannerNode::publish_path_to_goal(
  const geometry_msgs::msg::PoseStamped & /*goal*/)
{
  // TODO
}

}  // namespace path_planner

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<path_planner::PathPlannerNode>());
  rclcpp::shutdown();
  return 0;
}
