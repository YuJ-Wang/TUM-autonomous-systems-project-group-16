#pragma once

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <trajectory_msgs/msg/multi_dof_joint_trajectory.hpp>
#include <std_msgs/msg/string.hpp>

namespace quadrotor_controller {

class ControllerInterfaceNode : public rclcpp::Node {
public:
  ControllerInterfaceNode();

private:
  void setup_interfaces();

  // Called when a new planned trajectory arrives from trajectory_generator.
  void on_trajectory(const trajectory_msgs::msg::MultiDOFJointTrajectory::SharedPtr msg);

  // Called when odometry arrives — used for hover fallback.
  void on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg);

  // 100 Hz wall-timer: samples the active trajectory and streams setpoints
  // to the precompiled controller_node.
  void on_sample_timer();

  // 5 Hz watchdog: if NO trajectory has ever been received, publish a hover
  // command so the controller has something to track at startup.
  void on_watchdog();

  void publish_hover_command();

  // Interpolate position/velocity/acceleration between two trajectory points.
  trajectory_msgs::msg::MultiDOFJointTrajectoryPoint interpolate(
    const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & a,
    const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & b,
    double alpha) const;

  rclcpp::Subscription<trajectory_msgs::msg::MultiDOFJointTrajectory>::SharedPtr traj_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Publisher<trajectory_msgs::msg::MultiDOFJointTrajectory>::SharedPtr command_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;

  rclcpp::TimerBase::SharedPtr sample_timer_;   // 100 Hz — trajectory sampler
  rclcpp::TimerBase::SharedPtr watchdog_timer_; // 5 Hz   — pre-trajectory hover guard

  bool have_trajectory_{false};
  trajectory_msgs::msg::MultiDOFJointTrajectory active_traj_;
  rclcpp::Time traj_start_time_;

  bool have_odom_{false};
  nav_msgs::msg::Odometry latest_odom_;

  double trajectory_timeout_s_{5.0};
};

}  // namespace quadrotor_controller
