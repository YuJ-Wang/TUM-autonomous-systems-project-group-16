#include "path_planner/path_planner_node.hpp"
#include <cmath>
#include <queue>
#include <unordered_map>
#include <octomap/OcTree.h>
#include <octomap_msgs/conversions.h>

namespace path_planner {

PathPlannerNode::PathPlannerNode() : Node("path_planner_node")
{
  resolution_     = declare_parameter("map_resolution",    0.15);
  safety_margin_  = declare_parameter("safety_margin",     0.5);
  max_expansions_ = declare_parameter("max_expansions",    100000);
  waypoint_step_  = declare_parameter("waypoint_step",     3);

  odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
    "/current_state_est", 10,
    [this](nav_msgs::msg::Odometry::SharedPtr m){ odom_ = m; });

  goal_sub_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    "goal_pose", 10,
    std::bind(&PathPlannerNode::on_goal, this, std::placeholders::_1));

  octomap_sub_ = create_subscription<octomap_msgs::msg::Octomap>(
    "/octomap", 10,
    std::bind(&PathPlannerNode::on_octomap, this, std::placeholders::_1));

  path_pub_   = create_publisher<nav_msgs::msg::Path>("path", 10);
  status_pub_ = create_publisher<std_msgs::msg::String>("planner_status", 10);

  RCLCPP_INFO(get_logger(), "path_planner_node ready  (res=%.2f, margin=%.2f)", resolution_, safety_margin_);
}

// OctoMap callback

void PathPlannerNode::on_octomap(const octomap_msgs::msg::Octomap::SharedPtr msg)
{
  auto *tree = dynamic_cast<octomap::OcTree*>(octomap_msgs::fullMsgToMap(*msg));
  if (!tree) return;

  resolution_ = tree->getResolution();
  int margin  = std::max(1, (int)std::ceil(safety_margin_ / resolution_));

  // Collect raw occupied voxels first
  std::vector<Voxel> raw;
  for (auto it = tree->begin_leafs(); it != tree->end_leafs(); ++it) {
    if (tree->isNodeOccupied(*it)) {
      raw.push_back({(int)std::round(it.getX() / resolution_),
                     (int)std::round(it.getY() / resolution_),
                     (int)std::round(it.getZ() / resolution_)});
    }
  }
  delete tree;

  // expand every obstacle voxel by safety margin
  obstacles_.clear();
  for (auto & v : raw) {
    for (int dx = -margin; dx <= margin; ++dx)
      for (int dy = -margin; dy <= margin; ++dy)
        for (int dz = -margin; dz <= margin; ++dz)
          obstacles_.insert(vkey(v.x+dx, v.y+dy, v.z+dz));
  }

  map_ready_ = true;
  RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 5000,
    "OctoMap: %zu raw -> %zu inflated voxels", raw.size(), obstacles_.size());
}

// Goal callback

void PathPlannerNode::on_goal(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  geometry_msgs::msg::Point start;
  if (odom_) {
    start = odom_->pose.pose.position;
  } else {
    start = msg->pose.position; // no odom yet, degenerate path
  }

  auto path = (map_ready_ && !obstacles_.empty())
    ? plan_astar(start, msg->pose.position)
    : plan_straight_line(start, msg->pose.position);

  path_pub_->publish(path);

  std_msgs::msg::String s;
  s.data = "Path: " + std::to_string(path.poses.size()) + " pts";
  status_pub_->publish(s);
}

// A* planner

PathPlannerNode::Voxel PathPlannerNode::from_key(int64_t k)
{
  auto sign = [](int v){ return (v & 0x100000) ? (v | ~0x1FFFFF) : v; };
  return { sign((int)((k>>42)&0x1FFFFF)),
           sign((int)((k>>21)&0x1FFFFF)),
           sign((int)( k     &0x1FFFFF)) };
}

PathPlannerNode::Voxel PathPlannerNode::to_voxel(const geometry_msgs::msg::Point & p) const
{
  return { (int)std::round(p.x/resolution_),
           (int)std::round(p.y/resolution_),
           (int)std::round(p.z/resolution_) };
}

geometry_msgs::msg::Point PathPlannerNode::to_world(const Voxel & v) const
{
  geometry_msgs::msg::Point p;
  p.x = v.x * resolution_;
  p.y = v.y * resolution_;
  p.z = v.z * resolution_;
  return p;
}

nav_msgs::msg::Path PathPlannerNode::plan_astar(
  const geometry_msgs::msg::Point & start_pt,
  const geometry_msgs::msg::Point & goal_pt)
{
  Voxel s = to_voxel(start_pt), g = to_voxel(goal_pt);

  // Euclidean heuristic
  auto h = [&](int64_t k) -> double {
    Voxel v = from_key(k);
    double dx=v.x-g.x, dy=v.y-g.y, dz=v.z-g.z;
    return std::sqrt(dx*dx+dy*dy+dz*dz);
  };

  // Priority queue: (f-score, key)
  using Entry = std::pair<double, int64_t>;
  std::priority_queue<Entry, std::vector<Entry>, std::greater<>> pq;

  std::unordered_map<int64_t, double>  g_cost;
  std::unordered_map<int64_t, int64_t> parent;

  int64_t sk = vkey(s), gk = vkey(g);
  g_cost[sk] = 0.0;
  pq.push({h(sk), sk});

  int expanded = 0;
  bool found = false;

  while (!pq.empty() && expanded < max_expansions_) {
    auto [f, ck] = pq.top(); pq.pop();

    if (ck == gk) { found = true; break; }

    Voxel cur = from_key(ck);
    double cg = g_cost[ck];
    ++expanded;

    // 26-connected neighbors
    for (int dx=-1; dx<=1; ++dx)
    for (int dy=-1; dy<=1; ++dy)
    for (int dz=-1; dz<=1; ++dz) {
      if (dx==0 && dy==0 && dz==0) continue;
      Voxel nb{cur.x+dx, cur.y+dy, cur.z+dz};
      if (blocked(nb)) continue;

      double ng = cg + std::sqrt(dx*dx+dy*dy+dz*dz);
      int64_t nk = vkey(nb);
      if (!g_cost.count(nk) || ng < g_cost[nk]) {
        g_cost[nk] = ng;
        parent[nk] = ck;
        pq.push({ng + h(nk), nk});
      }
    }
  }

  // Reconstruct path
  nav_msgs::msg::Path path;
  path.header.stamp = now();
  path.header.frame_id = "world";

  if (found) {
    std::vector<Voxel> voxels;
    for (int64_t k = gk; parent.count(k); k = parent[k])
      voxels.push_back(from_key(k));
    voxels.push_back(s);
    std::reverse(voxels.begin(), voxels.end());

    // keep every waypoint_step_-th voxel + last
    for (size_t i = 0; i < voxels.size(); i += waypoint_step_) {
      geometry_msgs::msg::PoseStamped ps;
      ps.header = path.header;
      ps.pose.position = to_world(voxels[i]);
      ps.pose.orientation.w = 1.0;
      path.poses.push_back(ps);
    }
    // Always include the final goal
    if (!path.poses.empty()) {
      auto & last = path.poses.back().pose.position;
      auto gw = to_world(voxels.back());
      if (last.x != gw.x || last.y != gw.y || last.z != gw.z) {
        geometry_msgs::msg::PoseStamped ps;
        ps.header = path.header;
        ps.pose.position = gw;
        ps.pose.orientation.w = 1.0;
        path.poses.push_back(ps);
      }
    }

    RCLCPP_INFO(get_logger(), "A* path: %zu waypoints, %d expanded", path.poses.size(), expanded);
  } else {
    RCLCPP_WARN(get_logger(), "A* failed (%d expanded), falling back to straight line", expanded);
    return plan_straight_line(start_pt, goal_pt);
  }

  return path;
}

nav_msgs::msg::Path PathPlannerNode::plan_straight_line(
  const geometry_msgs::msg::Point & start,
  const geometry_msgs::msg::Point & goal)
{
  nav_msgs::msg::Path path;
  path.header.stamp = now();
  path.header.frame_id = "world";

  const int N = 20;
  for (int i = 0; i <= N; ++i) {
    double t = (double)i / N;
    geometry_msgs::msg::PoseStamped ps;
    ps.header = path.header;
    ps.pose.position.x = start.x + t * (goal.x - start.x);
    ps.pose.position.y = start.y + t * (goal.y - start.y);
    ps.pose.position.z = start.z + t * (goal.z - start.z);
    ps.pose.orientation.w = 1.0;
    path.poses.push_back(ps);
  }

  RCLCPP_INFO(get_logger(), "Straight-line path: %zu waypoints", path.poses.size());
  return path;
}

}  // namespace path_planner

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<path_planner::PathPlannerNode>());
  rclcpp::shutdown();
  return 0;
}
