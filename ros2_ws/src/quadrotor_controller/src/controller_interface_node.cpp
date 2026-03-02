#include <algorithm>
#include <chrono>
#include <cmath>
#include <sstream>

#include "quadrotor_controller/controller_interface_node.hpp"

namespace quadrotor_controller {

ControllerInterfaceNode::ControllerInterfaceNode()
: Node("controller_interface_node") {
  trajectory_timeout_s_ = this->declare_parameter<double>("trajectory_timeout_s", 5.0);
  setup_interfaces();
  // Capture wall-clock start time AFTER node init so this->now() is valid.
  node_start_time_ = this->now();
}

void ControllerInterfaceNode::setup_interfaces() {
  traj_sub_ = this->create_subscription<trajectory_msgs::msg::MultiDOFJointTrajectory>(
    "/planning/trajectory", 10,
    std::bind(&ControllerInterfaceNode::on_trajectory, this, std::placeholders::_1));

  odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
    "/current_state_est", 10,
    std::bind(&ControllerInterfaceNode::on_odometry, this, std::placeholders::_1));

  command_pub_ = this->create_publisher<trajectory_msgs::msg::MultiDOFJointTrajectory>(
    "/command/trajectory", 10);

  status_pub_ = this->create_publisher<std_msgs::msg::String>("/mission/status", 10);

  // 100 Hz wall-timer: streams trajectory setpoints to the controller, mirroring
  // the mav_trajectory_generation trajectory_sampler from the 2024 reference.
  sample_timer_ = this->create_wall_timer(
    std::chrono::milliseconds(10),
    std::bind(&ControllerInterfaceNode::on_sample_timer, this));

  // 5 Hz watchdog: hover fallback before the first trajectory ever arrives.
  watchdog_timer_ = this->create_wall_timer(
    std::chrono::milliseconds(200),
    std::bind(&ControllerInterfaceNode::on_watchdog, this));
}

// ---------------------------------------------------------------------------
// Callbacks
// ---------------------------------------------------------------------------

void ControllerInterfaceNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg) {
  latest_odom_ = *msg;
  have_odom_ = true;
}

void ControllerInterfaceNode::on_trajectory(
  const trajectory_msgs::msg::MultiDOFJointTrajectory::SharedPtr msg)
{
  if (msg->points.empty()) {
    return;
  }
  active_traj_ = *msg;
  traj_start_time_ = this->now();
  have_trajectory_ = true;
}

// ---------------------------------------------------------------------------
// 100 Hz trajectory sampler
// ---------------------------------------------------------------------------

void ControllerInterfaceNode::on_sample_timer() {
  if (!have_trajectory_) {
    return;  // watchdog handles the no-trajectory case
  }

  const auto & pts = active_traj_.points;
  const size_t n = pts.size();
  if (n == 0) {
    return;
  }

  // Elapsed seconds since the trajectory was received.
  const double t_elapsed = (this->now() - traj_start_time_).seconds();

  // Find which segment we are in.
  // points[i].time_from_start is the stamp of the i-th waypoint.
  trajectory_msgs::msg::MultiDOFJointTrajectoryPoint setpoint;

  if (t_elapsed <= 0.0 || n == 1) {
    setpoint = pts.front();
  } else {
    // Find last index whose time_from_start <= t_elapsed.
    size_t idx = n - 1;
    for (size_t i = 0; i + 1 < n; ++i) {
      const double t_i = rclcpp::Duration(pts[i].time_from_start).seconds();
      const double t_next = rclcpp::Duration(pts[i + 1].time_from_start).seconds();
      if (t_elapsed >= t_i && t_elapsed < t_next) {
        idx = i;
        break;
      }
    }

    if (idx + 1 >= n) {
      // Past the end of the trajectory — hold at the final waypoint.
      setpoint = pts.back();
    } else {
      const double t0 = rclcpp::Duration(pts[idx].time_from_start).seconds();
      const double t1 = rclcpp::Duration(pts[idx + 1].time_from_start).seconds();
      const double alpha = (t1 > t0) ? (t_elapsed - t0) / (t1 - t0) : 1.0;
      setpoint = interpolate(pts[idx], pts[idx + 1], std::clamp(alpha, 0.0, 1.0));
    }
  }

  // Wrap in a single-point MultiDOFJointTrajectory — this is what the
  // precompiled controller_node expects (same as 2024 trajectory sampler output).
  trajectory_msgs::msg::MultiDOFJointTrajectory cmd;
  cmd.header.stamp = this->now();
  cmd.header.frame_id = active_traj_.header.frame_id.empty() ? "world" : active_traj_.header.frame_id;
  cmd.points.push_back(setpoint);

  command_pub_->publish(cmd);
}

// ---------------------------------------------------------------------------
// Watchdog: hover guard before first trajectory arrives
// ---------------------------------------------------------------------------

void ControllerInterfaceNode::on_watchdog() {
  // Once we have a valid trajectory, the sample_timer handles everything.
  if (have_trajectory_) {
    return;
  }

  // Before the first trajectory arrives: check if enough time has passed
  // (measured from node start via sim time) to warrant a hover command.
  const double t_since_node_start = (this->now() - node_start_time_).seconds();
  if (t_since_node_start < trajectory_timeout_s_) {
    return;
  }

  std_msgs::msg::String status;
  status.data = "controller_interface: waiting for first trajectory — commanding hover";
  status_pub_->publish(status);

  publish_hover_command();
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

void ControllerInterfaceNode::publish_hover_command() {
  if (!have_odom_) {
    return;
  }

  trajectory_msgs::msg::MultiDOFJointTrajectory hover;
  hover.header.stamp = this->now();
  hover.header.frame_id = "world";

  trajectory_msgs::msg::MultiDOFJointTrajectoryPoint pt;
  pt.transforms.resize(1);
  pt.velocities.resize(1);
  pt.accelerations.resize(1);

  pt.transforms[0].translation.x = latest_odom_.pose.pose.position.x;
  pt.transforms[0].translation.y = latest_odom_.pose.pose.position.y;
  pt.transforms[0].translation.z = latest_odom_.pose.pose.position.z;
  pt.transforms[0].rotation      = latest_odom_.pose.pose.orientation;
  pt.time_from_start = rclcpp::Duration::from_seconds(0.0);

  hover.points.push_back(pt);
  command_pub_->publish(hover);
}

trajectory_msgs::msg::MultiDOFJointTrajectoryPoint ControllerInterfaceNode::interpolate(
  const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & a,
  const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & b,
  double alpha) const
{
  auto lerp = [](double x, double y, double t) { return x + t * (y - x); };

  trajectory_msgs::msg::MultiDOFJointTrajectoryPoint out;
  out.transforms.resize(1);
  out.velocities.resize(1);
  out.accelerations.resize(1);

  // Position (transform.translation)
  if (!a.transforms.empty() && !b.transforms.empty()) {
    out.transforms[0].translation.x = lerp(
      a.transforms[0].translation.x, b.transforms[0].translation.x, alpha);
    out.transforms[0].translation.y = lerp(
      a.transforms[0].translation.y, b.transforms[0].translation.y, alpha);
    out.transforms[0].translation.z = lerp(
      a.transforms[0].translation.z, b.transforms[0].translation.z, alpha);
    // Use the orientation of the leading point (yaw aligned with travel direction).
    out.transforms[0].rotation = b.transforms[0].rotation;
  }

  // Velocity
  if (!a.velocities.empty() && !b.velocities.empty()) {
    out.velocities[0].linear.x = lerp(
      a.velocities[0].linear.x, b.velocities[0].linear.x, alpha);
    out.velocities[0].linear.y = lerp(
      a.velocities[0].linear.y, b.velocities[0].linear.y, alpha);
    out.velocities[0].linear.z = lerp(
      a.velocities[0].linear.z, b.velocities[0].linear.z, alpha);
    out.velocities[0].angular.z = lerp(
      a.velocities[0].angular.z, b.velocities[0].angular.z, alpha);
  }

  // Acceleration
  if (!a.accelerations.empty() && !b.accelerations.empty()) {
    out.accelerations[0].linear.x = lerp(
      a.accelerations[0].linear.x, b.accelerations[0].linear.x, alpha);
    out.accelerations[0].linear.y = lerp(
      a.accelerations[0].linear.y, b.accelerations[0].linear.y, alpha);
    out.accelerations[0].linear.z = lerp(
      a.accelerations[0].linear.z, b.accelerations[0].linear.z, alpha);
  }

  out.time_from_start = rclcpp::Duration::from_seconds(
    lerp(rclcpp::Duration(a.time_from_start).seconds(),
         rclcpp::Duration(b.time_from_start).seconds(), alpha));

  return out;
}

}  // namespace quadrotor_controller

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<quadrotor_controller::ControllerInterfaceNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
