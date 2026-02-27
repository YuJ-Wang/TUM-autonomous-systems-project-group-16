#include "perception/depth_to_pointcloud_node.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<perception::DepthToPointCloudNode>());
    rclcpp::shutdown();
    return 0;
}
