#include <cmath>
#include <limits>

#include <cv_bridge/cv_bridge.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>

#include "perception_pipeline/depth_to_pointcloud_node.hpp"

namespace perception_pipeline {

DepthToPointcloudNode::DepthToPointcloudNode()
: Node("depth_to_pointcloud_node") {
  use_semantic_mask_ = this->declare_parameter<bool>("use_semantic_mask", true);
  min_depth_m_ = this->declare_parameter<double>("min_depth_m", 0.1);
  max_depth_m_ = this->declare_parameter<double>("max_depth_m", 30.0);
  setup_interfaces();
}

void DepthToPointcloudNode::setup_interfaces() {
  info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
    "/realsense/depth/camera_info", rclcpp::SensorDataQoS(),
    std::bind(&DepthToPointcloudNode::on_camera_info, this, std::placeholders::_1));

  mask_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/perception/semantic_mask", rclcpp::SensorDataQoS(),
    std::bind(&DepthToPointcloudNode::on_mask, this, std::placeholders::_1));

  depth_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/realsense/depth/image", rclcpp::SensorDataQoS(),
    std::bind(&DepthToPointcloudNode::on_depth_image, this, std::placeholders::_1));

  cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/perception/pointcloud", 10);
}

void DepthToPointcloudNode::on_camera_info(const sensor_msgs::msg::CameraInfo::SharedPtr msg) {
  camera_info_ = msg;
}

void DepthToPointcloudNode::on_mask(const sensor_msgs::msg::Image::SharedPtr msg) {
  semantic_mask_ = msg;
}

void DepthToPointcloudNode::on_depth_image(const sensor_msgs::msg::Image::SharedPtr msg) {
  if (!camera_info_) {
    return;
  }

  cv_bridge::CvImageConstPtr depth_cv;
  try {
    sensor_msgs::msg::Image::ConstSharedPtr depth_const = msg;
    depth_cv = cv_bridge::toCvShare(depth_const, sensor_msgs::image_encodings::TYPE_16UC1);
  } catch (const cv_bridge::Exception & ex) {
    RCLCPP_WARN(this->get_logger(), "depth conversion failed: %s", ex.what());
    return;
  }

  cv_bridge::CvImageConstPtr mask_cv;
  if (use_semantic_mask_ && semantic_mask_) {
    try {
      sensor_msgs::msg::Image::ConstSharedPtr mask_const = semantic_mask_;
      mask_cv = cv_bridge::toCvShare(mask_const, sensor_msgs::image_encodings::MONO8);
    } catch (const cv_bridge::Exception &) {
      mask_cv.reset();
    }
  }

  const double fx = camera_info_->k[0];
  const double fy = camera_info_->k[4];
  const double cx = camera_info_->k[2];
  const double cy = camera_info_->k[5];
  if (fx <= 0.0 || fy <= 0.0) {
    return;
  }

  sensor_msgs::msg::PointCloud2 cloud;
  cloud.header = msg->header;
  cloud.height = msg->height;
  cloud.width = msg->width;
  cloud.is_dense = false;
  cloud.is_bigendian = false;

  sensor_msgs::PointCloud2Modifier modifier(cloud);
  modifier.setPointCloud2FieldsByString(1, "xyz");
  modifier.resize(static_cast<size_t>(cloud.height) * static_cast<size_t>(cloud.width));

  sensor_msgs::PointCloud2Iterator<float> iter_x(cloud, "x");
  sensor_msgs::PointCloud2Iterator<float> iter_y(cloud, "y");
  sensor_msgs::PointCloud2Iterator<float> iter_z(cloud, "z");

  const float nan = std::numeric_limits<float>::quiet_NaN();

  for (int v = 0; v < depth_cv->image.rows; ++v) {
    const auto * depth_row = depth_cv->image.ptr<uint16_t>(v);
    const auto * mask_row =
      (mask_cv && v < mask_cv->image.rows) ? mask_cv->image.ptr<uint8_t>(v) : nullptr;

    for (int u = 0; u < depth_cv->image.cols; ++u, ++iter_x, ++iter_y, ++iter_z) {
      if (mask_row && mask_row[u] == 0) {
        *iter_x = nan;
        *iter_y = nan;
        *iter_z = nan;
        continue;
      }

      const uint16_t depth_mm = depth_row[u];
      if (depth_mm == 0) {
        *iter_x = nan;
        *iter_y = nan;
        *iter_z = nan;
        continue;
      }

      const double z = static_cast<double>(depth_mm) * 1e-3;
      if (z < min_depth_m_ || z > max_depth_m_) {
        *iter_x = nan;
        *iter_y = nan;
        *iter_z = nan;
        continue;
      }

      *iter_x = static_cast<float>((static_cast<double>(u) - cx) * z / fx);
      *iter_y = static_cast<float>((static_cast<double>(v) - cy) * z / fy);
      *iter_z = static_cast<float>(z);
    }
  }

  cloud_pub_->publish(cloud);
}

}  // namespace perception_pipeline

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<perception_pipeline::DepthToPointcloudNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
