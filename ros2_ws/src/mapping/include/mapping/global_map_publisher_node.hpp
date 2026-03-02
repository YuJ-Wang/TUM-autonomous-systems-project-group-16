#pragma once

#include <string>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <std_msgs/msg/string.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include "utils/msg/global_map.hpp"
#include "utils/msg/lantern_pose_array.hpp"
#include "utils/srv/save_map.hpp"

namespace mapping {

class GlobalMapPublisherNode : public rclcpp::Node {
public:
  GlobalMapPublisherNode();

private:
  void setup_interfaces();
  void on_map_raw(const utils::msg::GlobalMap::SharedPtr msg);
  void on_mission_state(const std_msgs::msg::String::SharedPtr msg);
  void on_lantern_poses(const utils::msg::LanternPoseArray::SharedPtr msg);
  void on_legacy_lantern_poses(const geometry_msgs::msg::PoseArray::SharedPtr msg);
  void publish_visualization(const utils::msg::GlobalMap & map);
  void auto_save_results();
  void on_save_map(
    const std::shared_ptr<utils::srv::SaveMap::Request> request,
    std::shared_ptr<utils::srv::SaveMap::Response> response);

  rclcpp::Subscription<utils::msg::GlobalMap>::SharedPtr map_sub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mission_state_sub_;
  rclcpp::Subscription<utils::msg::LanternPoseArray>::SharedPtr lantern_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr legacy_lantern_sub_;
  rclcpp::Publisher<utils::msg::GlobalMap>::SharedPtr map_pub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_pub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr frontier_marker_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
  rclcpp::Service<utils::srv::SaveMap>::SharedPtr save_map_srv_;

  utils::msg::GlobalMap latest_map_;
  utils::msg::LanternPoseArray latest_lanterns_;
  bool has_map_{false};
  bool results_saved_{false};
  std::string output_dir_;
};

}  // namespace mapping
