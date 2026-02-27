#include "perception/pointcloud_to_octomap_node.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<perception::PointCloudToOctomapNode>());
    rclcpp::shutdown();
    return 0;
}
