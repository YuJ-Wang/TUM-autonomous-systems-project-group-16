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
    "path_input", rclcpp::QoS(10),
    std::bind(&TrajectoryPlannerNode::on_path, this, std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "trajectory_planner_node: path_planner subscription");
    
  traj_pub_ = create_publisher<trajectory_msgs::msg::MultiDOFJointTrajectory>(
    "trajectory_output", rclcpp::QoS(10));

  RCLCPP_INFO(this->get_logger(), "trajectory_planner_node: trajectory_planner publisher");
  
  status_pub_ = create_publisher<std_msgs::msg::String>(
    "status", rclcpp::QoS(10));

  RCLCPP_INFO(this->get_logger(), "trajectory_planner_node: status publisher");
}

void TrajectoryPlannerNode::on_path(const nav_msgs::msg::Path::SharedPtr msg)
{
  if (msg->poses.empty()) {
    return;
  }
  
  trajectory_msgs::msg::MultiDOFJointTrajectory trajectory;
  trajectory.header.stamp = now();
  trajectory.header.frame_id = msg->header.frame_id;
  
  std::vector<double> segment_distances;
  double total_distance = 0.0;
  
  for (size_t i = 1; i < msg->poses.size(); ++i) {
    double dist = distance_between(
      msg->poses[i-1].pose.position,
      msg->poses[i].pose.position);
    segment_distances.push_back(dist);
    total_distance += dist;
  }

  double accel_distance = (desired_speed_ * desired_speed_) / (2.0 * max_acceleration_);
  
  double current_time = 0.0;
  
  for (size_t i = 0; i < msg->poses.size(); ++i) {
    trajectory_msgs::msg::MultiDOFJointTrajectoryPoint point;
    point.time_from_start = rclcpp::Duration::from_seconds(current_time);
    
    geometry_msgs::msg::Transform transform;
    transform.translation.x = msg->poses[i].pose.position.x;
    transform.translation.y = msg->poses[i].pose.position.y;
    transform.translation.z = msg->poses[i].pose.position.z;
    transform.rotation = msg->poses[i].pose.orientation;
    point.transforms.push_back(transform);
    
    trajectory.points.push_back(point);
    
    if (i < segment_distances.size()) {
      double speed = desired_speed_;
      double distance_remaining = total_distance - (total_distance - segment_distances[i]);
      
      // Determine if we're in acceleration, constant, or deceleration phase
      if (distance_remaining < accel_distance) {
        speed = std::sqrt(2.0 * max_acceleration_ * distance_remaining);
      } else if (distance_remaining < (total_distance - accel_distance)) {
        speed = desired_speed_;
      } else {
        speed = std::sqrt(2.0 * max_acceleration_ * (total_distance - distance_remaining));
      }
      
      current_time += std::max(segment_distances[i] / speed, min_segment_dt_);
    }
  }
  
  traj_pub_->publish(trajectory);
  
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
