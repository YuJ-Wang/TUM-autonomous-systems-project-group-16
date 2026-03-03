#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <sstream>

#include "state_machine/mission_state_machine_node.hpp"

namespace state_machine {

MissionStateMachineNode::MissionStateMachineNode()
: Node("mission_state_machine_node") {
  takeoff_altitude_ = this->declare_parameter<double>("takeoff_altitude", 10.0);
  cruise_altitude_ = this->declare_parameter<double>("cruise_altitude", 10.0);
  land_altitude_ = this->declare_parameter<double>("land_altitude", 0.4);
  arrival_tolerance_ = this->declare_parameter<double>("arrival_tolerance", 5.0);
  explore_timeout_s_ = this->declare_parameter<double>("explore_timeout_s", 420.0);
  desired_lantern_count_ = this->declare_parameter<int>("desired_lantern_count", 4);
  takeoff_timeout_s_ = this->declare_parameter<double>("takeoff_timeout_s", 45.0);
  entrance_timeout_s_ = this->declare_parameter<double>("entrance_timeout_s", 120.0);
  return_timeout_s_ = this->declare_parameter<double>("return_timeout_s", 150.0);
  land_timeout_s_ = this->declare_parameter<double>("land_timeout_s", 90.0);
  mission_hard_timeout_s_ = this->declare_parameter<double>("mission_hard_timeout_s", 1200.0);
  completion_grace_s_ = this->declare_parameter<double>("completion_grace_s", 2.0);
  lantern_summary_cooldown_s_ = this->declare_parameter<double>("lantern_summary_cooldown_s", 2.0);
  event_log_path_ = this->declare_parameter<std::string>("event_log_path", "statemachine_events.log");

  load_waypoints();
  setup_interfaces();
  last_goal_pub_time_ = this->now();
  last_lantern_summary_time_ = rclcpp::Time(0, 0, this->get_clock()->get_clock_type());

  // 每次启动都重置状态机事件日志，避免不同仿真轮次混在一起。
  std::ofstream reset_log(event_log_path_, std::ios::trunc);
}

void MissionStateMachineNode::setup_interfaces() {
  odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
    "/current_state_est", 10,
    std::bind(&MissionStateMachineNode::on_odometry, this, std::placeholders::_1));

  lantern_sub_ = this->create_subscription<utils::msg::LanternPoseArray>(
    "/perception/lantern_poses", 10,
    std::bind(&MissionStateMachineNode::on_lantern_poses, this, std::placeholders::_1));

  // Fallback for the legacy detector topic used in parts of the stack.
  legacy_lantern_sub_ = this->create_subscription<geometry_msgs::msg::PoseArray>(
    "/detected_lanterns", 10,
    std::bind(&MissionStateMachineNode::on_legacy_lantern_poses, this, std::placeholders::_1));

  map_sub_ = this->create_subscription<utils::msg::GlobalMap>(
    "/mapping/global_map", 10,
    std::bind(&MissionStateMachineNode::on_global_map, this, std::placeholders::_1));

  goal_pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/planning/goal", 10);
  state_pub_ = this->create_publisher<std_msgs::msg::String>("/mission/state", 10);
  lantern_summary_pub_ = this->create_publisher<std_msgs::msg::String>(
    "/statemachine/lantern_summary", 10);

  set_mode_srv_ = this->create_service<utils::srv::SetMissionMode>(
    "/mission/set_mode",
    std::bind(
      &MissionStateMachineNode::on_set_mode, this,
      std::placeholders::_1, std::placeholders::_2));

  timer_ = this->create_wall_timer(
    std::chrono::milliseconds(200),
    std::bind(&MissionStateMachineNode::tick, this));
}

void MissionStateMachineNode::load_waypoints() {
  std::vector<double> entrance_flat = this->declare_parameter<std::vector<double>>(
    "entrance_waypoints",
    std::vector<double>{-38.0, 10.0, 10.0, -1.57, -55.0, 0.84, 15.0, -1.57});
  std::vector<double> explore_flat = this->declare_parameter<std::vector<double>>(
    "explore_waypoints",
    std::vector<double>{});

  entrance_waypoints_.clear();
  constexpr size_t step = 4;
  for (size_t i = 0; i + step - 1 < entrance_flat.size(); i += step) {
    Waypoint wp;
    wp.x = entrance_flat[i];
    wp.y = entrance_flat[i + 1];
    wp.z = entrance_flat[i + 2];
    wp.yaw = entrance_flat[i + 3];
    entrance_waypoints_.push_back(wp);
  }

  explore_waypoints_.clear();
  // 如果 explore_waypoints 只给 x 值，则沿用当前旧配置的简化格式；如果按四元组给，则解析完整航点。
  if (!explore_flat.empty()) {
    if (explore_flat.size() % step == 0) {
      for (size_t i = 0; i + step - 1 < explore_flat.size(); i += step) {
        Waypoint wp;
        wp.x = explore_flat[i];
        wp.y = explore_flat[i + 1];
        wp.z = explore_flat[i + 2];
        wp.yaw = explore_flat[i + 3];
        explore_waypoints_.push_back(wp);
      }
    } else {
      for (double x_value : explore_flat) {
        Waypoint wp;
        wp.x = x_value;
        wp.y = 0.0;
        wp.z = std::max(cruise_altitude_, 5.0);
        wp.yaw = -M_PI / 2.0;
        explore_waypoints_.push_back(wp);
      }
    }
  }
}

void MissionStateMachineNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg) {
  have_odom_ = true;
  current_position_ = msg->pose.pose.position;
  if (!have_home_) {
    home_position_ = current_position_;
    have_home_ = true;
  }
}

void MissionStateMachineNode::on_lantern_poses(const utils::msg::LanternPoseArray::SharedPtr msg) {
  const uint32_t previous_count = confirmed_lanterns_;
  confirmed_lanterns_ = msg->confirmed_count;
  const geometry_msgs::msg::Point * latest_position = nullptr;
  if (!msg->lanterns.empty()) {
    latest_position = &msg->lanterns.back().pose.position;
  }
  maybe_publish_lantern_summary(previous_count, confirmed_lanterns_, latest_position);
}

void MissionStateMachineNode::on_legacy_lantern_poses(
  const geometry_msgs::msg::PoseArray::SharedPtr msg)
{
  const uint32_t previous_count = confirmed_lanterns_;
  const auto legacy_count = static_cast<uint32_t>(msg->poses.size());
  confirmed_lanterns_ = std::max(confirmed_lanterns_, legacy_count);
  const geometry_msgs::msg::Point * latest_position = nullptr;
  if (!msg->poses.empty()) {
    latest_position = &msg->poses.back().position;
  }
  maybe_publish_lantern_summary(previous_count, confirmed_lanterns_, latest_position);
}

void MissionStateMachineNode::on_global_map(const utils::msg::GlobalMap::SharedPtr msg) {
  map_valid_ = msg->valid;
  // Only store frontier goals while actively exploring — prevents stale frontiers
  // near the launch pad from hijacking the first EXPLORE navigation target.
  if (msg->frontier_goal_valid && state_ == MissionState::EXPLORE) {
    frontier_goal_ = msg->frontier_goal;
    frontier_goal_valid_ = true;
  }
}

bool MissionStateMachineNode::goal_reached() const {
  if (!goal_active_) {
    return false;
  }
  const double dx = current_position_.x - active_goal_.x;
  const double dy = current_position_.y - active_goal_.y;
  const double dz = current_position_.z - active_goal_.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz) <= arrival_tolerance_;
}

void MissionStateMachineNode::publish_goal(const Waypoint & wp) {
  geometry_msgs::msg::PoseStamped msg;
  msg.header.stamp = this->now();
  msg.header.frame_id = "world";
  msg.pose.position.x = wp.x;
  msg.pose.position.y = wp.y;
  msg.pose.position.z = wp.z;
  // Apply the waypoint yaw to the published goal orientation.
  tf2::Quaternion q;
  q.setRPY(0.0, 0.0, wp.yaw);
  msg.pose.orientation = tf2::toMsg(q);
  goal_pub_->publish(msg);
  active_goal_ = wp;
  goal_active_ = true;
  last_goal_pub_time_ = this->now();
}

void MissionStateMachineNode::append_event_log(const std::string & text) const {
  std::ofstream event_log(event_log_path_, std::ios::app);
  if (!event_log) {
    return;
  }
  event_log << text << '\n';
}

void MissionStateMachineNode::maybe_publish_lantern_summary(
  uint32_t previous_count, uint32_t new_count, const geometry_msgs::msg::Point * latest_position)
{
  if (new_count <= previous_count) {
    return;
  }

  std::ostringstream payload;
  payload << "count=" << new_count;
  if (latest_position != nullptr) {
    payload << ";x=" << latest_position->x
            << ";y=" << latest_position->y
            << ";z=" << latest_position->z;
  }

  pending_lantern_summaries_.push_back(payload.str());
  append_event_log("[Lantern] " + payload.str());
  flush_pending_lantern_summaries();
}

void MissionStateMachineNode::flush_pending_lantern_summaries() {
  if (pending_lantern_summaries_.empty()) {
    return;
  }

  const auto now = this->now();
  if (last_lantern_summary_time_.nanoseconds() != 0) {
    const double elapsed = (now - last_lantern_summary_time_).seconds();
    if (elapsed < lantern_summary_cooldown_s_) {
      return;
    }
  }

  std_msgs::msg::String summary_msg;
  summary_msg.data = pending_lantern_summaries_.front();
  pending_lantern_summaries_.pop_front();
  lantern_summary_pub_->publish(summary_msg);
  last_lantern_summary_time_ = now;
}

std::string MissionStateMachineNode::state_to_string(MissionState state) const {
  switch (state) {
    case MissionState::INIT: return "INIT";
    case MissionState::TAKEOFF: return "TAKEOFF";
    case MissionState::TO_CAVE_ENTRANCE: return "TO_CAVE_ENTRANCE";
    case MissionState::EXPLORE: return "EXPLORE";
    case MissionState::RETURN_HOME: return "RETURN_HOME";
    case MissionState::LAND: return "LAND";
    case MissionState::COMPLETE: return "COMPLETE";
    default: return "UNKNOWN";
  }
}

void MissionStateMachineNode::advance_waypoint(
  std::vector<Waypoint> & list, size_t & index, MissionState next_state)
{
  if (index >= list.size()) {
    state_ = next_state;
    goal_active_ = false;
    return;
  }

  publish_goal(list[index]);
  ++index;
}

void MissionStateMachineNode::on_set_mode(
  const std::shared_ptr<utils::srv::SetMissionMode::Request> request,
  std::shared_ptr<utils::srv::SetMissionMode::Response> response)
{
  const std::string mode = request->mode;
  bool accepted = true;
  std::string message;

  if (mode == "RETURN_HOME") {
    manual_hold_active_ = false;
    goal_active_ = false;
    state_ = MissionState::RETURN_HOME;
    return_started_ = false;
  } else if (mode == "LAND") {
    manual_hold_active_ = false;
    goal_active_ = false;
    state_ = MissionState::LAND;
    land_started_ = false;
  } else if (mode == "EXPLORE") {
    manual_hold_active_ = false;
    goal_active_ = false;
    frontier_goal_valid_ = false;
    explore_fallback_wp_started_ = false;
    explore_index_ = 0;
    state_ = MissionState::EXPLORE;
    explore_timer_started_ = false;
  } else if (mode == "HOLD") {
    manual_hold_active_ = true;
    Waypoint hold;
    hold.x = current_position_.x;
    hold.y = current_position_.y;
    hold.z = std::max(current_position_.z, land_altitude_);
    hold.yaw = 0.0;
    publish_goal(hold);
  } else {
    accepted = false;
    message = "Unsupported mode: " + mode;
  }

  response->success = accepted;
  response->active_mode = manual_hold_active_ ? "HOLD" : state_to_string(state_);
  response->message = accepted ? "Mode accepted" : message;
}

void MissionStateMachineNode::tick() {
  if (!have_odom_) {
    return;
  }

  std_msgs::msg::String state_msg;
  state_msg.data = manual_hold_active_ ? "HOLD" : state_to_string(state_);
  state_pub_->publish(state_msg);
  flush_pending_lantern_summaries();

  if (manual_hold_active_) {
    if (goal_active_ && (this->now() - last_goal_pub_time_).seconds() > 2.0) {
      publish_goal(active_goal_);
    }
    return;
  }

  if (
    mission_started_ &&
    mission_hard_timeout_s_ > 0.0 &&
    state_ != MissionState::COMPLETE &&
    (this->now() - mission_start_time_).seconds() > mission_hard_timeout_s_)
  {
    RCLCPP_WARN(
      this->get_logger(),
      "Mission hard timeout reached (%.0fs) — forcing RETURN_HOME",
      mission_hard_timeout_s_);
    state_ = MissionState::RETURN_HOME;
    return_started_ = false;
    goal_active_ = false;
  }

  switch (state_) {
    case MissionState::INIT: {
      if (!mission_started_) {
        mission_start_time_ = this->now();
        mission_started_ = true;
      }
      Waypoint takeoff;
      takeoff.x = home_position_.x;
      takeoff.y = home_position_.y;
      takeoff.z = takeoff_altitude_;
      takeoff.yaw = 0.0;
      publish_goal(takeoff);
      state_ = MissionState::TAKEOFF;
      break;
    }
    case MissionState::TAKEOFF: {
      if (!takeoff_started_) {
        takeoff_start_time_ = this->now();
        takeoff_started_ = true;
      }
      const bool takeoff_timed_out =
        (this->now() - takeoff_start_time_).seconds() > takeoff_timeout_s_;
      if (goal_reached() || takeoff_timed_out) {
        if (takeoff_timed_out) {
          RCLCPP_WARN(this->get_logger(),
            "TAKEOFF timeout (%.0fs) — forcing TO_CAVE_ENTRANCE", takeoff_timeout_s_);
        }
        if (entrance_waypoints_.empty()) {
          state_ = MissionState::EXPLORE;
        } else {
          entrance_index_ = 0;
          advance_waypoint(entrance_waypoints_, entrance_index_, MissionState::EXPLORE);
          state_ = MissionState::TO_CAVE_ENTRANCE;
        }
      } else if (goal_active_ && (this->now() - last_goal_pub_time_).seconds() > 2.0) {
        // Replanning loop: re-issue goal so path_planner replans from current position.
        publish_goal(active_goal_);
      }
      break;
    }
    case MissionState::TO_CAVE_ENTRANCE: {
      if (!entrance_started_) {
        entrance_start_time_ = this->now();
        entrance_started_ = true;
      }
      const bool entrance_timed_out =
        (this->now() - entrance_start_time_).seconds() > entrance_timeout_s_;
      if (goal_reached()) {
        entrance_start_time_ = this->now();  // reset per-waypoint timeout on success
        if (entrance_index_ < entrance_waypoints_.size()) {
          advance_waypoint(entrance_waypoints_, entrance_index_, MissionState::EXPLORE);
        } else {
          state_ = MissionState::EXPLORE;
          goal_active_ = false;
        }
      } else if (entrance_timed_out) {
        RCLCPP_WARN(this->get_logger(),
          "TO_CAVE_ENTRANCE waypoint timeout (%.0fs) — forcing next waypoint or EXPLORE",
          entrance_timeout_s_);
        entrance_start_time_ = this->now();
        if (entrance_index_ < entrance_waypoints_.size()) {
          advance_waypoint(entrance_waypoints_, entrance_index_, MissionState::EXPLORE);
        } else {
          state_ = MissionState::EXPLORE;
          goal_active_ = false;
        }
      } else if (goal_active_ && (this->now() - last_goal_pub_time_).seconds() > 2.0) {
        publish_goal(active_goal_);
      }
      break;
    }
    case MissionState::EXPLORE: {
      // Start exploration timer on entry and discard any frontiers captured before
      // EXPLORE began (they point to areas near the launch pad, not the cave interior).
      if (!explore_timer_started_) {
        explore_start_time_ = this->now();
        explore_timer_started_ = true;
        frontier_goal_valid_ = false;
        explore_fallback_wp_started_ = false;
        explore_index_ = 0;
        RCLCPP_INFO(this->get_logger(), "Cave exploration started. Frontier-based navigation active.");
      }

      const bool detected_all = confirmed_lanterns_ >= static_cast<uint32_t>(desired_lantern_count_);
      const double elapsed = (this->now() - explore_start_time_).seconds();
      const bool timeout = elapsed > explore_timeout_s_;

      if (detected_all || timeout) {
        RCLCPP_INFO(
          this->get_logger(),
          "Explore complete: lanterns=%u/%d, elapsed=%.1fs, timeout=%s",
          confirmed_lanterns_, desired_lantern_count_, elapsed, timeout ? "yes" : "no");
        state_ = MissionState::RETURN_HOME;
        return_started_ = false;
        goal_active_ = false;
        break;
      }

      // Per-fallback-waypoint timeout: if the corrupted state estimate prevents
      // goal_reached() from ever firing, force advance to the next waypoint.
      if (explore_fallback_wp_started_ && !frontier_goal_valid_ &&
          (this->now() - explore_fallback_wp_start_time_).seconds() > explore_fallback_wp_timeout_s_) {
        RCLCPP_WARN(this->get_logger(),
          "EXPLORE: fallback waypoint timeout (%.0fs) — forcing next waypoint",
          explore_fallback_wp_timeout_s_);
        explore_fallback_wp_started_ = false;
        goal_active_ = false;  // triggers the advance branch below on this same tick
      }

      // Primary: use frontier goals from the mapper to drive autonomous exploration.
      if (frontier_goal_valid_) {
        Waypoint frontier_wp;
        frontier_wp.x = frontier_goal_.x;
        frontier_wp.y = frontier_goal_.y;
        frontier_wp.z = std::max(frontier_goal_.z, 2.0);
        frontier_wp.yaw = std::atan2(
          frontier_wp.y - current_position_.y,
          frontier_wp.x - current_position_.x);
        publish_goal(frontier_wp);
        frontier_goal_valid_ = false;
        explore_fallback_wp_started_ = false;  // frontier took over
      } else if (goal_active_ && !goal_reached() &&
                 (this->now() - last_goal_pub_time_).seconds() > 2.0) {
        // Not yet at waypoint — re-publish to keep planner alive.
        publish_goal(active_goal_);
      } else if (!goal_active_ || goal_reached()) {
        if (explore_index_ < explore_waypoints_.size()) {
          Waypoint fallback_wp = explore_waypoints_[explore_index_++];
          // 对只给 x 的旧配置做就地适配：用当前位置 y 保持在通道内。
          if (std::abs(fallback_wp.y) < 1e-6) {
            fallback_wp.y = current_position_.y;
          }
          if (fallback_wp.z < 1e-6) {
            fallback_wp.z = std::max(current_position_.z, 5.0);
          }
          RCLCPP_INFO(this->get_logger(),
            "EXPLORE: using configured fallback waypoint (%.1f, %.1f, %.1f)",
            fallback_wp.x, fallback_wp.y, fallback_wp.z);
          publish_goal(fallback_wp);
          explore_fallback_wp_start_time_ = this->now();
          explore_fallback_wp_started_ = true;
          break;
        }

        // No frontier available: autonomously push 20 m deeper into the cave from
        // the current estimated position.  The goal is computed from live odometry
        // (not a predefined coordinate), so this satisfies the "no hardcoded cave
        // waypoints" requirement while still driving the depth camera into unmapped
        // space so the mapper can generate frontier goals.
        Waypoint push_wp;
        push_wp.x = current_position_.x - 20.0;  // cave runs in -x direction
        push_wp.y = current_position_.y;
        push_wp.z = std::max(current_position_.z, 5.0);
        push_wp.yaw = -M_PI / 2.0;  // face into cave
        RCLCPP_WARN(this->get_logger(),
          "EXPLORE: no frontier — pushing 20m deeper to (%.1f, %.1f, %.1f)",
          push_wp.x, push_wp.y, push_wp.z);
        publish_goal(push_wp);
        explore_fallback_wp_start_time_ = this->now();
        explore_fallback_wp_started_ = true;
      }
      break;
    }
    case MissionState::RETURN_HOME: {
      if (!return_started_) {
        return_start_time_ = this->now();
        return_started_ = true;
      }
      const bool return_timed_out =
        (this->now() - return_start_time_).seconds() > return_timeout_s_;
      if (!goal_active_) {
        Waypoint home;
        home.x = home_position_.x;
        home.y = home_position_.y;
        home.z = cruise_altitude_;
        home.yaw = 0.0;
        publish_goal(home);
      } else if (goal_reached()) {
        state_ = MissionState::LAND;
        land_started_ = false;
        goal_active_ = false;
      } else if (return_timed_out) {
        RCLCPP_WARN(
          this->get_logger(),
          "RETURN_HOME timeout (%.0fs) — forcing LAND",
          return_timeout_s_);
        state_ = MissionState::LAND;
        land_started_ = false;
        goal_active_ = false;
      } else if ((this->now() - last_goal_pub_time_).seconds() > 2.0) {
        publish_goal(active_goal_);
      }
      break;
    }
    case MissionState::LAND: {
      if (!land_started_) {
        land_start_time_ = this->now();
        land_started_ = true;
      }
      const bool land_timed_out =
        (this->now() - land_start_time_).seconds() > land_timeout_s_;
      if (!goal_active_) {
        Waypoint land;
        land.x = home_position_.x;
        land.y = home_position_.y;
        land.z = land_altitude_;
        land.yaw = 0.0;
        publish_goal(land);
      } else if (current_position_.z <= land_altitude_ + 1.5 || land_timed_out) {
        if (land_timed_out) {
          RCLCPP_WARN(
            this->get_logger(),
            "LAND timeout (%.0fs) — forcing COMPLETE",
            land_timeout_s_);
        }
        state_ = MissionState::COMPLETE;
        goal_active_ = false;
      } else if ((this->now() - last_goal_pub_time_).seconds() > 2.0) {
        publish_goal(active_goal_);
      }
      break;
    }
    case MissionState::COMPLETE: {
      if (!mission_summary_reported_) {
        const double elapsed_s =
          mission_started_ ? (this->now() - mission_start_time_).seconds() : 0.0;
        RCLCPP_INFO(
          this->get_logger(),
          "MISSION COMPLETE | lanterns_found=%u/%d | mission_time=%.1fs",
          confirmed_lanterns_, desired_lantern_count_, elapsed_s);
        mission_complete_time_ = this->now();
        mission_summary_reported_ = true;
      }
      if (!shutdown_requested_ &&
          (this->now() - mission_complete_time_).seconds() >= completion_grace_s_) {
        shutdown_requested_ = true;
        RCLCPP_INFO(this->get_logger(), "Shutting down mission node.");
        rclcpp::shutdown();
      }
      break;
    }
    default:
      break;
  }
}

}  // namespace state_machine

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<state_machine::MissionStateMachineNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
