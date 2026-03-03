#pragma once

#include <string>
#include <vector>
#include <deque>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include "utils/msg/global_map.hpp"
#include "utils/msg/lantern_pose_array.hpp"
#include "utils/srv/set_mission_mode.hpp"

namespace state_machine {

class MissionStateMachineNode : public rclcpp::Node {
public:
  MissionStateMachineNode();

private:
  enum class MissionState {
    INIT,
    TAKEOFF,
    TO_CAVE_ENTRANCE,
    EXPLORE,
    RETURN_HOME,
    LAND,
    COMPLETE
  };

  struct Waypoint {
    double x{0.0};
    double y{0.0};
    double z{0.0};
    double yaw{0.0};
  };

  void setup_interfaces();
  void load_waypoints();
  void tick();
  void publish_goal(const Waypoint & wp);
  bool goal_reached() const;
  std::string state_to_string(MissionState state) const;
  void advance_waypoint(std::vector<Waypoint> & list, size_t & index, MissionState next_state);
  void maybe_publish_lantern_summary(uint32_t previous_count, uint32_t new_count,
    const geometry_msgs::msg::Point * latest_position);
  void flush_pending_lantern_summaries();
  void append_event_log(const std::string & text) const;

  void on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg);
  void on_lantern_poses(const utils::msg::LanternPoseArray::SharedPtr msg);
  void on_legacy_lantern_poses(const geometry_msgs::msg::PoseArray::SharedPtr msg);
  void on_global_map(const utils::msg::GlobalMap::SharedPtr msg);
  void on_set_mode(
    const std::shared_ptr<utils::srv::SetMissionMode::Request> request,
    std::shared_ptr<utils::srv::SetMissionMode::Response> response);

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<utils::msg::LanternPoseArray>::SharedPtr lantern_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr legacy_lantern_sub_;
  rclcpp::Subscription<utils::msg::GlobalMap>::SharedPtr map_sub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr lantern_summary_pub_;
  rclcpp::Service<utils::srv::SetMissionMode>::SharedPtr set_mode_srv_;
  rclcpp::TimerBase::SharedPtr timer_;

  MissionState state_{MissionState::INIT};
  std::vector<Waypoint> entrance_waypoints_;
  std::vector<Waypoint> explore_waypoints_;  // emergency fallback only
  size_t entrance_index_{0};
  size_t explore_index_{0};
  bool manual_hold_active_{false};

  bool have_odom_{false};
  bool have_home_{false};
  geometry_msgs::msg::Point current_position_;
  Waypoint active_goal_;
  bool goal_active_{false};
  geometry_msgs::msg::Point home_position_;
  uint32_t confirmed_lanterns_{0};
  uint32_t announced_lanterns_{0};
  bool map_valid_{false};

  geometry_msgs::msg::Point frontier_goal_;
  bool frontier_goal_valid_{false};

  double takeoff_altitude_{10.0};
  double cruise_altitude_{10.0};
  double land_altitude_{0.4};
  double arrival_tolerance_{5.0};
  double explore_timeout_s_{420.0};
  int desired_lantern_count_{4};
  rclcpp::Time explore_start_time_;
  bool explore_timer_started_{false};

  double takeoff_timeout_s_{45.0};
  double entrance_timeout_s_{120.0};
  double return_timeout_s_{150.0};
  double land_timeout_s_{90.0};
  double mission_hard_timeout_s_{1200.0};
  double completion_grace_s_{2.0};
  rclcpp::Time takeoff_start_time_;
  bool takeoff_started_{false};
  rclcpp::Time entrance_start_time_;
  bool entrance_started_{false};
  rclcpp::Time return_start_time_;
  bool return_started_{false};
  rclcpp::Time land_start_time_;
  bool land_started_{false};

  rclcpp::Time last_goal_pub_time_;
  rclcpp::Time last_lantern_summary_time_;
  rclcpp::Time mission_start_time_;
  bool mission_started_{false};
  bool mission_summary_reported_{false};
  rclcpp::Time mission_complete_time_;
  bool shutdown_requested_{false};

  // Per-fallback-waypoint timeout in EXPLORE (prevents getting stuck when
  // corrupted state estimate prevents goal_reached() from ever firing).
  double explore_fallback_wp_timeout_s_{90.0};
  rclcpp::Time explore_fallback_wp_start_time_;
  bool explore_fallback_wp_started_{false};
  double lantern_summary_cooldown_s_{2.0};
  std::deque<std::string> pending_lantern_summaries_;
  std::string event_log_path_{"statemachine_events.log"};
};

}  // namespace state_machine
