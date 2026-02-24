#pragma once

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <nav_msgs/msg/path.hpp>
#include <trajectory_msgs/msg/multi_dof_joint_trajectory.hpp>
#include <std_msgs/msg/string.hpp>

namespace trajectory_planner {

class TrajectoryGeneratorNode : public rclcpp::Node {
public:
  TrajectoryGeneratorNode();

private:
  void setup_interfaces();
  void on_path(const nav_msgs::msg::Path::SharedPtr msg);
  double distance_between(
    const geometry_msgs::msg::Point & a,
    const geometry_msgs::msg::Point & b) const;

  rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr path_sub_;
  rclcpp::Publisher<trajectory_msgs::msg::MultiDOFJointTrajectory>::SharedPtr traj_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;

  double desired_speed_{2.0};
  double min_segment_dt_{0.05};
  double max_acceleration_{1.5};
};

}  // namespace trajectory_planner
