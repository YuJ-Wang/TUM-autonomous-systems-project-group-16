#include "state_machine/mission_state_machine_node.hpp"

namespace state_machine {

MissionStateMachineNode::MissionStateMachineNode()
: Node("mission_state_machine_node")
{
  // TODO: declare parameters (takeoff_altitude, cruise_altitude, land_altitude,
  //       arrival_tolerance, explore_timeout_s, desired_lantern_count,
  //       takeoff_timeout_s, entrance_timeout_s, entrance_waypoints, explore_waypoints)
  load_waypoints();
  setup_interfaces();
  last_goal_pub_time_ = this->now();
}

void MissionStateMachineNode::setup_interfaces()
{
  // TODO: create odom/lantern/map subscriptions, goal/state publishers,
  //       SetMissionMode service, and 200ms tick timer
}

void MissionStateMachineNode::load_waypoints()
{
  // TODO: parse entrance_waypoints and explore_waypoints from flat double vectors
}

void MissionStateMachineNode::tick()
{
  // TODO: FSM tick — dispatch on state_ and transition between states
}

void MissionStateMachineNode::publish_goal(const Waypoint & /*wp*/)
{
  // TODO: build PoseStamped from Waypoint (x,y,z,yaw) and publish to /planning/goal
}

bool MissionStateMachineNode::goal_reached() const
{
  // TODO: return true when distance(current_position_, active_goal_) < arrival_tolerance_
  return false;
}

std::string MissionStateMachineNode::state_to_string(MissionState /*state*/) const
{
  // TODO
  return "";
}

void MissionStateMachineNode::advance_waypoint(
  std::vector<Waypoint> & /*list*/, size_t & /*index*/, MissionState /*next_state*/)
{
  // TODO: increment waypoint index; if exhausted, transition to next_state
}

void MissionStateMachineNode::on_odometry(
  const nav_msgs::msg::Odometry::SharedPtr /*msg*/)
{
  // TODO: update current_position_, record home on first call
}

void MissionStateMachineNode::on_lantern_poses(
  const utils::msg::LanternPoseArray::SharedPtr /*msg*/)
{
  // TODO: update confirmed_lanterns_
}

void MissionStateMachineNode::on_global_map(
  const utils::msg::GlobalMap::SharedPtr /*msg*/)
{
  // TODO: update map_valid_, frontier_goal_, frontier_goal_valid_
}

void MissionStateMachineNode::on_set_mode(
  const std::shared_ptr<utils::srv::SetMissionMode::Request> /*request*/,
  std::shared_ptr<utils::srv::SetMissionMode::Response> /*response*/)
{
  // TODO: handle manual mode override requests
}

}  // namespace state_machine

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<state_machine::MissionStateMachineNode>());
  rclcpp::shutdown();
  return 0;
}
