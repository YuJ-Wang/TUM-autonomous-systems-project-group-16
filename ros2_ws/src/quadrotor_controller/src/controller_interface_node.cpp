#include "quadrotor_controller/controller_interface_node.hpp"

namespace quadrotor_controller {

ControllerInterfaceNode::ControllerInterfaceNode()
: Node("controller_interface_node")
{
  // TODO: declare parameters (trajectory_timeout_s)
  setup_interfaces();
}

void ControllerInterfaceNode::setup_interfaces()
{
  // TODO: create traj/odom subscriptions, command publisher, 100Hz and 5Hz timers
}

void ControllerInterfaceNode::on_trajectory(
  const trajectory_msgs::msg::MultiDOFJointTrajectory::SharedPtr /*msg*/)
{
  // TODO: store trajectory, record start time, set have_trajectory_
}

void ControllerInterfaceNode::on_odometry(
  const nav_msgs::msg::Odometry::SharedPtr /*msg*/)
{
  // TODO: store latest odometry for hover fallback
}

void ControllerInterfaceNode::on_sample_timer()
{
  // TODO: compute elapsed time, find active segment, publish interpolated setpoint
}

void ControllerInterfaceNode::on_watchdog()
{
  // TODO: publish hover command if no trajectory has been received yet
}

void ControllerInterfaceNode::publish_hover_command()
{
  // TODO: build single-point hover trajectory at current odom position and publish
}

trajectory_msgs::msg::MultiDOFJointTrajectoryPoint ControllerInterfaceNode::interpolate(
  const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & /*a*/,
  const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & /*b*/,
  double /*alpha*/) const
{
  // TODO
  return trajectory_msgs::msg::MultiDOFJointTrajectoryPoint{};
}

}  // namespace quadrotor_controller

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<quadrotor_controller::ControllerInterfaceNode>());
  rclcpp::shutdown();
  return 0;
}
