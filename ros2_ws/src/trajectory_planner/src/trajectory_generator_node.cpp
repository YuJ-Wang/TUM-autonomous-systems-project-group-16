#include "trajectory_planner/trajectory_generator_node.hpp"

namespace trajectory_planner {

TrajectoryGeneratorNode::TrajectoryGeneratorNode()
: Node("trajectory_generator_node")
{
  // TODO: declare parameters (desired_speed, min_segment_dt, max_acceleration)
  setup_interfaces();
}

void TrajectoryGeneratorNode::setup_interfaces()
{
  // TODO: create path subscriber, trajectory publisher, status publisher
}

void TrajectoryGeneratorNode::on_path(const nav_msgs::msg::Path::SharedPtr /*msg*/)
{
  // TODO: build MultiDOFJointTrajectory with trapezoidal speed profile
}

double TrajectoryGeneratorNode::distance_between(
  const geometry_msgs::msg::Point & /*a*/,
  const geometry_msgs::msg::Point & /*b*/) const
{
  // TODO
  return 0.0;
}

}  // namespace trajectory_planner

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<trajectory_planner::TrajectoryGeneratorNode>());
  rclcpp::shutdown();
  return 0;
}
