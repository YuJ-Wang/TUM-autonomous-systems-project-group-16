#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include "utils/msg/global_map.hpp"
#include "utils/srv/save_map.hpp"

namespace mapping {

class GlobalMapPublisherNode : public rclcpp::Node {
public:
  GlobalMapPublisherNode();

private:
  void setup_interfaces();
  void on_map_raw(const utils::msg::GlobalMap::SharedPtr msg);
  void on_save_map(
    const std::shared_ptr<utils::srv::SaveMap::Request> request,
    std::shared_ptr<utils::srv::SaveMap::Response> response);

  rclcpp::Subscription<utils::msg::GlobalMap>::SharedPtr map_sub_;
  rclcpp::Publisher<utils::msg::GlobalMap>::SharedPtr map_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
  rclcpp::Service<utils::srv::SaveMap>::SharedPtr save_map_srv_;

  utils::msg::GlobalMap latest_map_;
  bool has_map_{false};
};

}  // namespace mapping
