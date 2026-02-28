#include "trajectory_planner/trajectory_planner_node.hpp"

namespace trajectory_planner {

TrajectoryPlannerNode::TrajectoryPlannerNode()
: Node("trajectory_planner_node")
{
  desired_speed_ = declare_parameter("desired_speed", 2.0);
  min_segment_dt_ = declare_parameter("min_segment_dt", 0.05);
  max_acceleration_ = declare_parameter("max_acceleration", 1.5);
  setup_interfaces();
}

void TrajectoryPlannerNode::setup_interfaces()
{
  path_sub_ = create_subscription<nav_msgs::msg::Path>(
    "path", rclcpp::QoS(10),
    std::bind(&TrajectoryPlannerNode::on_path, this, std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "trajectory_planner_node: subscribed to path (from path_planner)");
    
  traj_pub_ = create_publisher<trajectory_msgs::msg::MultiDOFJointTrajectory>(
    "command/trajectory", rclcpp::QoS(10));

  RCLCPP_INFO(this->get_logger(), "trajectory_planner_node: publishing on command/trajectory");
  
  status_pub_ = create_publisher<std_msgs::msg::String>(
    "trajectory_status", rclcpp::QoS(10));

  RCLCPP_INFO(this->get_logger(), "trajectory_planner_node: status publisher on trajectory_status");
}

void TrajectoryPlannerNode::on_path(const nav_msgs::msg::Path::SharedPtr msg)
{
  if (msg->poses.empty()) {
    return;
  }
  
  trajectory_msgs::msg::MultiDOFJointTrajectory trajectory;
  trajectory.header.stamp = now();
  trajectory.header.frame_id = msg->header.frame_id;
  trajectory.joint_names.push_back("base_link");
  
  // Compute per-segment distances and cumulative distance from start
  std::vector<double> segment_distances;
  std::vector<double> cumulative_distance;  // distance from start at each waypoint
  double total_distance = 0.0;
  cumulative_distance.push_back(0.0);
  
  for (size_t i = 1; i < msg->poses.size(); ++i) {
    double dist = distance_between(
      msg->poses[i-1].pose.position,
      msg->poses[i].pose.position);
    segment_distances.push_back(dist);
    total_distance += dist;
    cumulative_distance.push_back(total_distance);
  }

  if (total_distance < 1e-6) {
    RCLCPP_WARN(this->get_logger(), "Path has near-zero length, skipping");
    return;
  }

  // Trapezoidal velocity profile distances
  double accel_distance = (desired_speed_ * desired_speed_) / (2.0 * max_acceleration_);
  // If path is too short to reach full speed, split evenly
  if (2.0 * accel_distance > total_distance) {
    accel_distance = total_distance / 2.0;
  }
  double decel_start = total_distance - accel_distance;
  
  double current_time = 0.0;
  
  for (size_t i = 0; i < msg->poses.size(); ++i) {
    double dist_from_start = cumulative_distance[i];
    double dist_to_end = total_distance - dist_from_start;
    
    // Compute speed at this waypoint using trapezoidal profile
    double speed;
    if (dist_from_start < accel_distance) {
      // Acceleration phase
      speed = std::max(std::sqrt(2.0 * max_acceleration_ * dist_from_start), 0.1);
    } else if (dist_from_start > decel_start) {
      // Deceleration phase
      speed = std::max(std::sqrt(2.0 * max_acceleration_ * dist_to_end), 0.1);
    } else {
      // Constant speed phase
      speed = desired_speed_;
    }
    
    trajectory_msgs::msg::MultiDOFJointTrajectoryPoint point;
    point.time_from_start = rclcpp::Duration::from_seconds(current_time);
    
    // Position (transform)
    geometry_msgs::msg::Transform transform;
    transform.translation.x = msg->poses[i].pose.position.x;
    transform.translation.y = msg->poses[i].pose.position.y;
    transform.translation.z = msg->poses[i].pose.position.z;
    transform.rotation = msg->poses[i].pose.orientation;
    point.transforms.push_back(transform);
    
    // Velocity — direction toward next waypoint, scaled by speed
    geometry_msgs::msg::Twist vel;
    if (i + 1 < msg->poses.size()) {
      double seg_dist = segment_distances[i];
      if (seg_dist > 1e-6) {
        double dx = msg->poses[i+1].pose.position.x - msg->poses[i].pose.position.x;
        double dy = msg->poses[i+1].pose.position.y - msg->poses[i].pose.position.y;
        double dz = msg->poses[i+1].pose.position.z - msg->poses[i].pose.position.z;
        vel.linear.x = (dx / seg_dist) * speed;
        vel.linear.y = (dy / seg_dist) * speed;
        vel.linear.z = (dz / seg_dist) * speed;
      }
    }
    // Last point: zero velocity (stop)
    point.velocities.push_back(vel);
    
    // Zero acceleration hint
    geometry_msgs::msg::Twist accel;
    point.accelerations.push_back(accel);
    
    trajectory.points.push_back(point);
    
    // Compute time to next waypoint
    if (i < segment_distances.size()) {
      double avg_speed = std::max(speed, 0.1);
      current_time += std::max(segment_distances[i] / avg_speed, min_segment_dt_);
    }
  }
  
  traj_pub_->publish(trajectory);
  
  RCLCPP_INFO(this->get_logger(), "Trajectory published: %zu points, %.1f m, %.1f s",
    trajectory.points.size(), total_distance, current_time);
  
  auto status_msg = std::make_unique<std_msgs::msg::String>();
  status_msg->data = "Trajectory generated with " + std::to_string(trajectory.points.size()) + " waypoints";
  status_pub_->publish(std::move(status_msg));
}

double TrajectoryPlannerNode::distance_between(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b) const
{
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  double dz = a.z - b.z;
  return std::sqrt(dx*dx + dy*dy + dz*dz);
}

}  // namespace trajectory_planner

int main(int argc, char ** argv)
{
  std::cout << "TrajectoryPlannerNode starting..." << std::endl;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<trajectory_planner::TrajectoryPlannerNode>());
  rclcpp::shutdown();
  return 0;
}
