#include "path_planner/path_planner_node.hpp"
#include <algorithm>
#include <cmath>
#include <unordered_map>

namespace path_planner {

PathPlannerNode::PathPlannerNode()
: Node("path_planner_node")
{
  // TODO: declare parameters
  map_resolution_ = declare_parameter("map_resolution", 0.5);
  interpolation_points_ = declare_parameter("interpolation_points", 30);
  min_flight_altitude_ = declare_parameter("min_flight_altitude", 2.0);
  safety_radius_m_ = declare_parameter("safety_radius_m", 1.0);
  astar_max_expansions_ = declare_parameter("astar_max_expansions", 120000);
  astar_search_margin_vox_ = declare_parameter("astar_search_margin_vox", 10);
  use_diagonal_moves_ = declare_parameter("use_diagonal_moves", true);
  planner_method_ = declare_parameter("planner_method", std::string("astar"));
  setup_interfaces();
}

void PathPlannerNode::setup_interfaces()
{
  odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
    "odometry/filtered", rclcpp::QoS(10),
    std::bind(&PathPlannerNode::on_odometry, this, std::placeholders::_1));
  
  RCLCPP_INFO(this->get_logger(), "path_planner_node: odometry subscription");

  goal_sub_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    "goal_pose", rclcpp::QoS(10),
    std::bind(&PathPlannerNode::on_goal, this, std::placeholders::_1));
  
  RCLCPP_INFO(this->get_logger(), "path_planner_node: goal subscription");

  frontier_goal_sub_ = create_subscription<geometry_msgs::msg::Point>(
    "frontier_goal", rclcpp::QoS(10),
    std::bind(&PathPlannerNode::on_frontier_goal, this, std::placeholders::_1));
  
  RCLCPP_INFO(this->get_logger(), "path_planner_node: frontier goal subscription");

  map_sub_ = create_subscription<utils::msg::GlobalMap>(
    "global_map", rclcpp::QoS(10),
    std::bind(&PathPlannerNode::on_global_map, this, std::placeholders::_1));
  
  RCLCPP_INFO(this->get_logger(), "path_planner_node: global map subscription");
  
  path_pub_ = create_publisher<nav_msgs::msg::Path>("path", rclcpp::QoS(10));
  RCLCPP_INFO(this->get_logger(), "path_planner_node: path publisher");
  status_pub_ = create_publisher<std_msgs::msg::String>("status", rclcpp::QoS(10));
  RCLCPP_INFO(this->get_logger(), "path_planner_node: status publisher");
  
  RCLCPP_INFO(this->get_logger(), "path_planner_node initialized");
}

void PathPlannerNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  latest_odom_ = *msg;
}

void PathPlannerNode::on_goal(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  if (!map_valid_) {
    RCLCPP_WARN(this->get_logger(), "Received goal but map not valid yet");
    return;
  }
  publish_path_to_goal(*msg);
}

void PathPlannerNode::on_frontier_goal(const geometry_msgs::msg::Point::SharedPtr msg)
{
  if (!map_valid_) {
    RCLCPP_WARN(this->get_logger(), "Received frontier goal but map not valid yet");
    return;
  }
  geometry_msgs::msg::PoseStamped goal;
  goal.header.frame_id = "map";
  goal.header.stamp = now();
  goal.pose.position = *msg;
  goal.pose.position.z = std::max(goal.pose.position.z, min_flight_altitude_);
  goal.pose.orientation.w = 1.0;
  publish_path_to_goal(goal);
}

void PathPlannerNode::on_global_map(const utils::msg::GlobalMap::SharedPtr msg)
{
  map_resolution_ = msg->resolution;
  map_has_occupancy_ = msg->occupied_voxels > 0;
  occupied_voxels_.clear();
  
  // Extract occupied voxel coordinates from the separate arrays
  for (size_t i = 0; i < msg->occupied_ix.size() && i < msg->occupied_iy.size() && i < msg->occupied_iz.size(); ++i) {
    int64_t key = pack_key(msg->occupied_ix[i], msg->occupied_iy[i], msg->occupied_iz[i]);
    occupied_voxels_.insert(key);
  }
  
  map_valid_ = msg->valid;
  RCLCPP_INFO(this->get_logger(), "Updated map with %u occupied voxels", msg->occupied_voxels);
}

int64_t PathPlannerNode::pack_key(int x, int y, int z)
{
  // Bit shifting to pack 3 coordinates into 64-bit int
  // Assumes coordinates fit in 21 bits (-1M to +1M range)
  int64_t key = 0;
  key |= ((int64_t)(x & 0x1FFFFF)) << 42;
  key |= ((int64_t)(y & 0x1FFFFF)) << 21;
  key |= ((int64_t)(z & 0x1FFFFF));
  return key;
}

PathPlannerNode::VoxelCoord PathPlannerNode::unpack_key(int64_t key)
{
  VoxelCoord coord;
  coord.x = (int)((key >> 42) & 0x1FFFFF);
  coord.y = (int)((key >> 21) & 0x1FFFFF);
  coord.z = (int)(key & 0x1FFFFF);
  // Handle sign extension for negative numbers
  if (coord.x & 0x100000) coord.x |= ~0x1FFFFF;
  if (coord.y & 0x100000) coord.y |= ~0x1FFFFF;
  if (coord.z & 0x100000) coord.z |= ~0x1FFFFF;
  return coord;
}

PathPlannerNode::VoxelCoord PathPlannerNode::world_to_voxel(
  const geometry_msgs::msg::Point & p) const
{
  VoxelCoord coord;
  coord.x = (int)std::round(p.x / map_resolution_);
  coord.y = (int)std::round(p.y / map_resolution_);
  coord.z = (int)std::round(p.z / map_resolution_);
  return coord;
}

geometry_msgs::msg::Point PathPlannerNode::voxel_to_world_center(
  const VoxelCoord & v) const
{
  geometry_msgs::msg::Point p;
  p.x = v.x * map_resolution_;
  p.y = v.y * map_resolution_;
  p.z = v.z * map_resolution_;
  return p;
}

bool PathPlannerNode::is_occupied(const VoxelCoord & voxel) const
{
  int64_t key = pack_key(voxel.x, voxel.y, voxel.z);
  return occupied_voxels_.find(key) != occupied_voxels_.end();
}

std::optional<PathPlannerNode::VoxelCoord> PathPlannerNode::find_nearest_free(
  const VoxelCoord & start, int max_radius) const
{
  if (!is_occupied(start)) {
    return start;
  }
  
  for (int radius = 1; radius <= max_radius; ++radius) {
    for (int dx = -radius; dx <= radius; ++dx) {
      for (int dy = -radius; dy <= radius; ++dy) {
        for (int dz = -radius; dz <= radius; ++dz) {
          // Only check voxels on the surface of the sphere
          if (std::abs(dx) != radius && std::abs(dy) != radius && std::abs(dz) != radius) {
            continue;
          }
          VoxelCoord candidate{start.x + dx, start.y + dy, start.z + dz};
          if (!is_occupied(candidate)) {
            return candidate;
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
  std::vector<VoxelCoord> path;
  
  // A* implementation
  auto heuristic = [](const VoxelCoord & a, const VoxelCoord & b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int dz = a.z - b.z;
    // Chebyshev distance (max of absolute differences)
    return std::max({std::abs(dx), std::abs(dy), std::abs(dz)});
  };
  
  std::unordered_map<int64_t, double> g_score;
  std::unordered_map<int64_t, int64_t> came_from;
  std::vector<std::pair<double, int64_t>> open_set; // priority queue
  
  int64_t start_key = pack_key(start.x, start.y, start.z);
  int64_t goal_key = pack_key(goal.x, goal.y, goal.z);
  
  g_score[start_key] = 0.0;
  open_set.push_back({heuristic(start, goal), start_key});
  
  int expansions = 0;
  const int max_expansions = astar_max_expansions_;
  
  while (!open_set.empty() && expansions < max_expansions) {
    std::sort(open_set.begin(), open_set.end());
    auto [f_score, current_key] = open_set.front();
    open_set.erase(open_set.begin());
    
    if (current_key == goal_key) {
      // Reconstruct path
      int64_t key = goal_key;
      while (came_from.find(key) != came_from.end()) {
        VoxelCoord coord = unpack_key(key);
        path.insert(path.begin(), coord);
        key = came_from[key];
      }
      path.insert(path.begin(), start);
      return path;
    }
    
    VoxelCoord current = unpack_key(current_key);
    double current_g = g_score[current_key];
    ++expansions;
    
    // Check all neighbors (6-connected or 26-connected)
    int step = use_diagonal_moves_ ? 1 : 1;
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        for (int dz = -1; dz <= 1; ++dz) {
          if (dx == 0 && dy == 0 && dz == 0) continue;
          
          VoxelCoord neighbor{current.x + dx, current.y + dy, current.z + dz};
          if (is_occupied(neighbor)) continue;
          
          double move_cost = std::sqrt(dx*dx + dy*dy + dz*dz);
          double tentative_g = current_g + move_cost;
          
          int64_t neighbor_key = pack_key(neighbor.x, neighbor.y, neighbor.z);
          if (g_score.find(neighbor_key) == g_score.end() || tentative_g < g_score[neighbor_key]) {
            came_from[neighbor_key] = current_key;
            g_score[neighbor_key] = tentative_g;
            double f = tentative_g + heuristic(neighbor, goal);
            open_set.push_back({f, neighbor_key});
          }
        }
      }
    }
  }
  
  // Return straight line if no path found
  path.push_back(start);
  path.push_back(goal);
  return path;
}

nav_msgs::msg::Path PathPlannerNode::build_straight_line_path(
  const geometry_msgs::msg::PoseStamped & goal) const
{
  nav_msgs::msg::Path path;
  path.header.frame_id = goal.header.frame_id;
  path.header.stamp = now();
  
  if (!latest_odom_) {
    path.poses.push_back(goal);
    return path;
  }
  
  geometry_msgs::msg::PoseStamped start_pose;
  start_pose.header.frame_id = goal.header.frame_id;
  start_pose.header.stamp = now();
  start_pose.pose.position.x = latest_odom_->pose.pose.position.x;
  start_pose.pose.position.y = latest_odom_->pose.pose.position.y;
  start_pose.pose.position.z = latest_odom_->pose.pose.position.z;
  start_pose.pose.orientation = latest_odom_->pose.pose.orientation;
  
  // Interpolate between start and goal
  for (int i = 0; i <= interpolation_points_; ++i) {
    double t = (interpolation_points_ > 0) ? (double)i / interpolation_points_ : 1.0;
    
    geometry_msgs::msg::PoseStamped pose;
    pose.header.frame_id = goal.header.frame_id;
    pose.header.stamp = now();
    
    // Linear interpolation
    pose.pose.position.x = start_pose.pose.position.x + t * (goal.pose.position.x - start_pose.pose.position.x);
    pose.pose.position.y = start_pose.pose.position.y + t * (goal.pose.position.y - start_pose.pose.position.y);
    pose.pose.position.z = start_pose.pose.position.z + t * (goal.pose.position.z - start_pose.pose.position.z);
    
    // Use goal orientation at the end
    pose.pose.orientation = (t > 0.5) ? goal.pose.orientation : start_pose.pose.orientation;
    
    path.poses.push_back(pose);
  }
  
  return path;
}

void PathPlannerNode::publish_path_to_goal(
  const geometry_msgs::msg::PoseStamped & goal)
{
  RCLCPP_INFO(this->get_logger(), "Planning path to goal: (%.2f, %.2f, %.2f)",
    goal.pose.position.x, goal.pose.position.y, goal.pose.position.z);
  
  nav_msgs::msg::Path path;
  
  if (planner_method_ == "astar" && map_valid_ && map_has_occupancy_) {
    // Use A* planner
    if (!latest_odom_) {
      RCLCPP_WARN(this->get_logger(), "No odometry yet, using straight line");
      path = build_straight_line_path(goal);
    } else {
      geometry_msgs::msg::Point start_point = latest_odom_->pose.pose.position;
      VoxelCoord start_voxel = world_to_voxel(start_point);
      VoxelCoord goal_voxel = world_to_voxel(goal.pose.position);
      
      // Find nearest free voxels if needed
      auto start_free = find_nearest_free(start_voxel, astar_search_margin_vox_);
      auto goal_free = find_nearest_free(goal_voxel, astar_search_margin_vox_);
      
      if (!start_free || !goal_free) {
        RCLCPP_WARN(this->get_logger(), "Could not find free voxels, using straight line");
        path = build_straight_line_path(goal);
      } else {
        std::vector<VoxelCoord> voxel_path = run_astar(*start_free, *goal_free);
        
        path.header.frame_id = goal.header.frame_id;
        path.header.stamp = now();
        for (const auto & voxel : voxel_path) {
          geometry_msgs::msg::PoseStamped pose;
          pose.header.frame_id = goal.header.frame_id;
          pose.header.stamp = now();
          pose.pose.position = voxel_to_world_center(voxel);
          pose.pose.orientation = goal.pose.orientation;
          path.poses.push_back(pose);
        }
      }
    }
  } else {
    // Use straight line planner
    path = build_straight_line_path(goal);
  }
  
  path_pub_->publish(path);
  
  auto status_msg = std::make_unique<std_msgs::msg::String>();
  status_msg->data = "Path published with " + std::to_string(path.poses.size()) + " waypoints";
  status_pub_->publish(std::move(status_msg));
}

}  // namespace path_planner

int main(int argc, char ** argv)
{
  std::cout << "PathPlannerNode starting..." << std::endl;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<path_planner::PathPlannerNode>());
  rclcpp::shutdown();
  return 0;
}
