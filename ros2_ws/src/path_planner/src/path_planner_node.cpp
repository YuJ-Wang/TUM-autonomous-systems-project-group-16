#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <queue>
#include <sstream>
#include <unordered_map>

#include "path_planner/path_planner_node.hpp"

namespace path_planner {

namespace {
constexpr int64_t kVoxelBias = 1 << 20;
constexpr int64_t kVoxelMask = (1 << 21) - 1;
}  // namespace

int64_t PathPlannerNode::pack_key(int x, int y, int z) {
  const int64_t xx = static_cast<int64_t>(x) + kVoxelBias;
  const int64_t yy = static_cast<int64_t>(y) + kVoxelBias;
  const int64_t zz = static_cast<int64_t>(z) + kVoxelBias;
  return (xx << 42) | (yy << 21) | zz;
}

PathPlannerNode::VoxelCoord PathPlannerNode::unpack_key(int64_t key) {
  VoxelCoord out;
  out.x = static_cast<int>((key >> 42) & kVoxelMask) - static_cast<int>(kVoxelBias);
  out.y = static_cast<int>((key >> 21) & kVoxelMask) - static_cast<int>(kVoxelBias);
  out.z = static_cast<int>(key & kVoxelMask) - static_cast<int>(kVoxelBias);
  return out;
}

PathPlannerNode::PathPlannerNode()
: Node("path_planner_node") {
  interpolation_points_ = this->declare_parameter<int>("interpolation_points", 30);
  min_flight_altitude_ = this->declare_parameter<double>("min_flight_altitude", 2.0);
  safety_radius_m_ = this->declare_parameter<double>("safety_radius_m", 1.0);
  astar_max_expansions_ = this->declare_parameter<int>("astar_max_expansions", 120000);
  astar_search_margin_vox_ = this->declare_parameter<int>("astar_search_margin_vox", 10);
  use_diagonal_moves_ = this->declare_parameter<bool>("use_diagonal_moves", true);
  planner_method_ = this->declare_parameter<std::string>("planner_method", "astar");
  setup_interfaces();
}

void PathPlannerNode::setup_interfaces() {
  odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
    "/current_state_est", 10,
    std::bind(&PathPlannerNode::on_odometry, this, std::placeholders::_1));

  goal_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
    "/planning/goal", 10,
    std::bind(&PathPlannerNode::on_goal, this, std::placeholders::_1));

  map_sub_ = this->create_subscription<utils::msg::GlobalMap>(
    "/mapping/global_map", 10,
    std::bind(&PathPlannerNode::on_global_map, this, std::placeholders::_1));

  path_pub_ = this->create_publisher<nav_msgs::msg::Path>("/planning/path", 10);
  status_pub_ = this->create_publisher<std_msgs::msg::String>("/planning/status", 10);
}

void PathPlannerNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg) {
  latest_odom_ = *msg;
}

void PathPlannerNode::on_global_map(const utils::msg::GlobalMap::SharedPtr msg) {
  map_valid_ = msg->valid;
  map_resolution_ = msg->resolution > 1e-6f ? static_cast<double>(msg->resolution) : 0.5;
  occupied_voxels_.clear();
  occupied_voxels_.reserve(msg->occupied_ix.size());
  for (size_t i = 0; i < msg->occupied_ix.size(); ++i) {
    occupied_voxels_.insert(pack_key(msg->occupied_ix[i], msg->occupied_iy[i], msg->occupied_iz[i]));
  }
  map_has_occupancy_ = !occupied_voxels_.empty();
}

PathPlannerNode::VoxelCoord PathPlannerNode::world_to_voxel(const geometry_msgs::msg::Point & p) const {
  VoxelCoord out;
  out.x = static_cast<int>(std::floor(p.x / map_resolution_));
  out.y = static_cast<int>(std::floor(p.y / map_resolution_));
  out.z = static_cast<int>(std::floor(p.z / map_resolution_));
  return out;
}

geometry_msgs::msg::Point PathPlannerNode::voxel_to_world_center(const VoxelCoord & v) const {
  geometry_msgs::msg::Point p;
  p.x = (static_cast<double>(v.x) + 0.5) * map_resolution_;
  p.y = (static_cast<double>(v.y) + 0.5) * map_resolution_;
  p.z = (static_cast<double>(v.z) + 0.5) * map_resolution_;
  return p;
}

bool PathPlannerNode::is_occupied(const VoxelCoord & voxel) const {
  if (!map_has_occupancy_) {
    return false;
  }

  const int inflate_vox = std::max(0, static_cast<int>(std::ceil(safety_radius_m_ / map_resolution_)));
  for (int dx = -inflate_vox; dx <= inflate_vox; ++dx) {
    for (int dy = -inflate_vox; dy <= inflate_vox; ++dy) {
      for (int dz = -inflate_vox; dz <= inflate_vox; ++dz) {
        if ((dx * dx + dy * dy + dz * dz) > (inflate_vox * inflate_vox)) {
          continue;
        }
        const int64_t key = pack_key(voxel.x + dx, voxel.y + dy, voxel.z + dz);
        if (occupied_voxels_.find(key) != occupied_voxels_.end()) {
          return true;
        }
      }
    }
  }
  return false;
}

std::optional<PathPlannerNode::VoxelCoord> PathPlannerNode::find_nearest_free(
  const VoxelCoord & start, int max_radius) const
{
  if (!is_occupied(start)) {
    return start;
  }

  for (int r = 1; r <= max_radius; ++r) {
    for (int dx = -r; dx <= r; ++dx) {
      for (int dy = -r; dy <= r; ++dy) {
        for (int dz = -r; dz <= r; ++dz) {
          if (std::max({std::abs(dx), std::abs(dy), std::abs(dz)}) != r) {
            continue;
          }
          VoxelCoord cand{start.x + dx, start.y + dy, start.z + dz};
          const geometry_msgs::msg::Point wp = voxel_to_world_center(cand);
          if (wp.z < min_flight_altitude_) {
            continue;
          }
          if (!is_occupied(cand)) {
            return cand;
          }
        }
      }
    }
  }
  return std::nullopt;
}

std::vector<PathPlannerNode::VoxelCoord> PathPlannerNode::run_astar(
  const VoxelCoord & start, const VoxelCoord & goal) const
{
  struct OpenNode {
    int64_t key;
    double f;
    double g;
  };
  struct CompareNode {
    bool operator()(const OpenNode & a, const OpenNode & b) const { return a.f > b.f; }
  };

  auto heuristic = [](const VoxelCoord & a, const VoxelCoord & b) {
      const double dx = static_cast<double>(a.x - b.x);
      const double dy = static_cast<double>(a.y - b.y);
      const double dz = static_cast<double>(a.z - b.z);
      return std::sqrt(dx * dx + dy * dy + dz * dz);
    };

  const int min_x = std::min(start.x, goal.x) - astar_search_margin_vox_;
  const int max_x = std::max(start.x, goal.x) + astar_search_margin_vox_;
  const int min_y = std::min(start.y, goal.y) - astar_search_margin_vox_;
  const int max_y = std::max(start.y, goal.y) + astar_search_margin_vox_;
  const int min_z = std::min(start.z, goal.z) - astar_search_margin_vox_;
  const int max_z = std::max(start.z, goal.z) + astar_search_margin_vox_;

  std::priority_queue<OpenNode, std::vector<OpenNode>, CompareNode> open;
  std::unordered_map<int64_t, double> g_score;
  std::unordered_map<int64_t, int64_t> came_from;

  const int64_t start_key = pack_key(start.x, start.y, start.z);
  const int64_t goal_key = pack_key(goal.x, goal.y, goal.z);
  g_score[start_key] = 0.0;
  open.push(OpenNode{start_key, heuristic(start, goal), 0.0});

  int expansions = 0;
  while (!open.empty() && expansions < astar_max_expansions_) {
    const OpenNode current = open.top();
    open.pop();
    const auto score_it = g_score.find(current.key);
    if (score_it == g_score.end() || current.g > score_it->second + 1e-9) {
      continue;
    }

    if (current.key == goal_key) {
      std::vector<VoxelCoord> path;
      int64_t k = goal_key;
      while (true) {
        path.push_back(unpack_key(k));
        if (k == start_key) {
          break;
        }
        auto it = came_from.find(k);
        if (it == came_from.end()) {
          return {};
        }
        k = it->second;
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    const VoxelCoord cv = unpack_key(current.key);
    ++expansions;

    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        for (int dz = -1; dz <= 1; ++dz) {
          if (dx == 0 && dy == 0 && dz == 0) {
            continue;
          }
          const int move_rank = std::abs(dx) + std::abs(dy) + std::abs(dz);
          if (!use_diagonal_moves_ && move_rank != 1) {
            continue;
          }

          VoxelCoord nv{cv.x + dx, cv.y + dy, cv.z + dz};
          if (
            nv.x < min_x || nv.x > max_x ||
            nv.y < min_y || nv.y > max_y ||
            nv.z < min_z || nv.z > max_z)
          {
            continue;
          }

          const geometry_msgs::msg::Point wp = voxel_to_world_center(nv);
          if (wp.z < min_flight_altitude_) {
            continue;
          }

          if (is_occupied(nv)) {
            continue;
          }

          const int64_t nk = pack_key(nv.x, nv.y, nv.z);
          const double step_cost = std::sqrt(
            static_cast<double>(dx * dx + dy * dy + dz * dz));
          const double tentative_g = current.g + step_cost;
          auto it = g_score.find(nk);
          if (it == g_score.end() || tentative_g < it->second) {
            g_score[nk] = tentative_g;
            came_from[nk] = current.key;
            const double f = tentative_g + heuristic(nv, goal);
            open.push(OpenNode{nk, f, tentative_g});
          }
        }
      }
    }
  }

  return {};
}

void PathPlannerNode::on_goal(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
  publish_path_to_goal(*msg);
}

nav_msgs::msg::Path PathPlannerNode::build_straight_line_path(
  const geometry_msgs::msg::PoseStamped & goal) const
{
  nav_msgs::msg::Path path_msg;
  path_msg.header.stamp = this->now();
  path_msg.header.frame_id = "world";

  if (!latest_odom_.has_value()) {
    return path_msg;
  }

  const auto & odom = latest_odom_.value();
  const int n = std::max(2, interpolation_points_);
  path_msg.poses.reserve(static_cast<size_t>(n));

  const double x0 = odom.pose.pose.position.x;
  const double y0 = odom.pose.pose.position.y;
  const double z0 = odom.pose.pose.position.z;  // use actual position; goal clamped below
  const double x1 = goal.pose.position.x;
  const double y1 = goal.pose.position.y;
  const double z1 = std::max(goal.pose.position.z, min_flight_altitude_);

  for (int i = 0; i < n; ++i) {
    const double t = static_cast<double>(i) / static_cast<double>(n - 1);
    geometry_msgs::msg::PoseStamped pose;
    pose.header = path_msg.header;
    pose.pose.position.x = x0 + t * (x1 - x0);
    pose.pose.position.y = y0 + t * (y1 - y0);
    pose.pose.position.z = z0 + t * (z1 - z0);
    pose.pose.orientation.w = 1.0;
    path_msg.poses.push_back(pose);
  }
  return path_msg;
}

void PathPlannerNode::publish_path_to_goal(const geometry_msgs::msg::PoseStamped & goal) {
  if (!latest_odom_.has_value()) {
    RCLCPP_WARN(this->get_logger(), "Path planner has no odometry yet, skipping goal");
    return;
  }

  nav_msgs::msg::Path path_msg;
  std::string mode = "astar";

  if (!map_valid_ || !map_has_occupancy_) {
    path_msg = build_straight_line_path(goal);
    mode = "fallback_straight";
  } else {
    geometry_msgs::msg::Point start_point = latest_odom_->pose.pose.position;
    start_point.z = std::max(start_point.z, min_flight_altitude_);

    geometry_msgs::msg::Point goal_point = goal.pose.position;
    goal_point.z = std::max(goal_point.z, min_flight_altitude_);

    std::optional<VoxelCoord> start_v = find_nearest_free(world_to_voxel(start_point), 5);
    std::optional<VoxelCoord> goal_v = find_nearest_free(world_to_voxel(goal_point), 8);

    if (!start_v.has_value() || !goal_v.has_value()) {
      path_msg = build_straight_line_path(goal);
      mode = "fallback_blocked_endpoints";
    } else {
      const std::vector<VoxelCoord> vox_path = run_astar(start_v.value(), goal_v.value());
      if (vox_path.empty()) {
        path_msg = build_straight_line_path(goal);
        mode = "fallback_astar_failed";
      } else {
        path_msg.header.stamp = this->now();
        path_msg.header.frame_id = "world";
        path_msg.poses.reserve(vox_path.size() + 1);

        for (const VoxelCoord & voxel : vox_path) {
          geometry_msgs::msg::PoseStamped pose;
          pose.header = path_msg.header;
          pose.pose.position = voxel_to_world_center(voxel);
          pose.pose.orientation.w = 1.0;
          path_msg.poses.push_back(pose);
        }

        // Ensure last path point exactly matches the high-level goal.
        geometry_msgs::msg::PoseStamped final_pose;
        final_pose.header = path_msg.header;
        final_pose.pose = goal.pose;
        final_pose.pose.position.z = std::max(final_pose.pose.position.z, min_flight_altitude_);
        path_msg.poses.push_back(final_pose);
      }
    }
  }

  path_pub_->publish(path_msg);

  std_msgs::msg::String status;
  std::ostringstream ss;
  ss << "path_published points=" << path_msg.poses.size()
     << " map_valid=" << (map_valid_ ? "true" : "false")
     << " occupancy=" << (map_has_occupancy_ ? "true" : "false")
     << " method=" << planner_method_
     << " mode=" << mode;
  status.data = ss.str();
  status_pub_->publish(status);
}

}  // namespace path_planner

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<path_planner::PathPlannerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
