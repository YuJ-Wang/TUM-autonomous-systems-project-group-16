#include "detection/lantern_detector_node.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<detection::LanternDetectorNode>());
    rclcpp::shutdown();
    return 0;
}
