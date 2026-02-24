#include "mapping/global_map_publisher_node.hpp"

namespace mapping {

GlobalMapPublisherNode::GlobalMapPublisherNode()
: Node("global_map_publisher_node")
{
  // TODO: declare parameters
  setup_interfaces();
}

void GlobalMapPublisherNode::setup_interfaces()
{
  // TODO: create subscriptions, publishers, and service
}

void GlobalMapPublisherNode::on_map_raw(const utils::msg::GlobalMap::SharedPtr /*msg*/)
{
  // TODO
}

void GlobalMapPublisherNode::on_save_map(
  const std::shared_ptr<utils::srv::SaveMap::Request> /*request*/,
  std::shared_ptr<utils::srv::SaveMap::Response> /*response*/)
{
  // TODO
}

}  // namespace mapping

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<mapping::GlobalMapPublisherNode>());
  rclcpp::shutdown();
  return 0;
}
