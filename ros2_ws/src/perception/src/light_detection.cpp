#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <cv_bridge/cv_bridge.hpp>

class LightDetectionNode : public rclcpp::Node {
public:
  LightDetectionNode()
  : Node("light_detection_node"),
    tf_buffer_(this->get_clock()),
    tf_listener_(tf_buffer_)
  {
    // TODO: declare parameters (semantic_image_topic, depth_image_topic,
    //       depth_info_topic, target_frame, mask_b/g/r, mask_tolerance,
    //       min/max_valid_depth_m, min_mask_pixels, unique_distance_m)
    // TODO: create subscribers and publisher
  }

private:
  void handleSemanticImage(const sensor_msgs::msg::Image::SharedPtr msg);
  void handleDepthImage(const sensor_msgs::msg::Image::SharedPtr msg);
  void handleCameraInfo(const sensor_msgs::msg::CameraInfo::SharedPtr msg);

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr semantic_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_sub_;
  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr cam_info_sub_;
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_pub_;

  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;

  std::string semantic_image_topic_;
  std::string depth_image_topic_;
  std::string depth_info_topic_;
  std::string target_frame_{"world"};
  int mask_b_{4};
  int mask_g_{235};
  int mask_r_{255};
  int mask_tolerance_{0};
  double min_valid_depth_m_{0.1};
  double max_valid_depth_m_{50.0};
  int min_mask_pixels_{30};
  double unique_distance_m_{10.0};
};

void LightDetectionNode::handleSemanticImage(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO
}

void LightDetectionNode::handleDepthImage(
  const sensor_msgs::msg::Image::SharedPtr /*msg*/)
{
  // TODO
}

void LightDetectionNode::handleCameraInfo(
  const sensor_msgs::msg::CameraInfo::SharedPtr /*msg*/)
{
  // TODO
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LightDetectionNode>());
  rclcpp::shutdown();
  return 0;
}
