#pragma once

#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <std_msgs/msg/string.hpp>
#include <octomap_msgs/msg/octomap.hpp>

namespace path_planner {

class PathPlannerNode : public rclcpp::Node {
public:
  PathPlannerNode();

private:
  // ── Callbacks ──
  void on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg);
  void on_goal(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
  void on_octomap(const octomap_msgs::msg::Octomap::SharedPtr msg);

  // ── Planning ──
  nav_msgs::msg::Path plan_astar(
    const geometry_msgs::msg::Point & start,
    const geometry_msgs::msg::Point & goal);
  nav_msgs::msg::Path plan_straight_line(
    const geometry_msgs::msg::Point & start,
    const geometry_msgs::msg::Point & goal);

  // ── Voxel helpers ──
  struct Voxel { int x, y, z; };
  Voxel to_voxel(const geometry_msgs::msg::Point & p) const;
  geometry_msgs::msg::Point to_world(const Voxel & v) const;

  static int64_t vkey(int x, int y, int z) {
    return ((int64_t)(x & 0x1FFFFF) << 42) |
           ((int64_t)(y & 0x1FFFFF) << 21) |
           ((int64_t)(z & 0x1FFFFF));
  }
  static int64_t vkey(const Voxel & v) { return vkey(v.x, v.y, v.z); }
  static Voxel from_key(int64_t k);

  bool blocked(const Voxel & v) const {
    return obstacles_.count(vkey(v));
  }

  // ── ROS interfaces ──
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_sub_;
  rclcpp::Subscription<octomap_msgs::msg::Octomap>::SharedPtr octomap_sub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;

  // ── State ──
  nav_msgs::msg::Odometry::SharedPtr odom_;
  std::unordered_set<int64_t> obstacles_;   // pre-inflated obstacle set
  bool map_ready_{false};

  // ── Parameters ──
  double resolution_{0.15};
  double safety_margin_{0.5};
  int max_expansions_{100000};
  int waypoint_step_{3};
};

}  // namespace path_planner
