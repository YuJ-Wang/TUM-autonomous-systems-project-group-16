#pragma once

#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <std_msgs/msg/string.hpp>

#include "utils/msg/global_map.hpp"

namespace path_planner {

class PathPlannerNode : public rclcpp::Node {
public:
  PathPlannerNode();

private:
  struct VoxelCoord {
    int x{0};
    int y{0};
    int z{0};
  };

  void setup_interfaces();
  void on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg);
  void on_goal(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
  void on_global_map(const utils::msg::GlobalMap::SharedPtr msg);

  static int64_t pack_key(int x, int y, int z);
  static VoxelCoord unpack_key(int64_t key);
  VoxelCoord world_to_voxel(const geometry_msgs::msg::Point & p) const;
  geometry_msgs::msg::Point voxel_to_world_center(const VoxelCoord & v) const;
  bool is_occupied(const VoxelCoord & voxel) const;
  std::optional<VoxelCoord> find_nearest_free(const VoxelCoord & start, int max_radius) const;
  std::vector<VoxelCoord> run_astar(const VoxelCoord & start, const VoxelCoord & goal) const;
  nav_msgs::msg::Path build_straight_line_path(const geometry_msgs::msg::PoseStamped & goal) const;
  void publish_path_to_goal(const geometry_msgs::msg::PoseStamped & goal);

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_sub_;
  rclcpp::Subscription<utils::msg::GlobalMap>::SharedPtr map_sub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;

  std::optional<nav_msgs::msg::Odometry> latest_odom_;
  bool map_valid_{false};
  bool map_has_occupancy_{false};
  std::unordered_set<int64_t> occupied_voxels_;
  double map_resolution_{0.5};
  int interpolation_points_{30};
  double min_flight_altitude_{2.0};
  double safety_radius_m_{1.0};
  int astar_max_expansions_{120000};
  int astar_search_margin_vox_{10};
  bool use_diagonal_moves_{true};
  std::string planner_method_{"astar"};
};

}  // namespace path_planner
