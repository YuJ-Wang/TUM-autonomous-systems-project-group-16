#include <cmath>

#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/imgproc.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <tf2/time.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include "perception_pipeline/object_detection_node.hpp"

namespace perception_pipeline {

ObjectDetectionNode::ObjectDetectionNode()
: Node("object_detection_node"),
  tf_buffer_(this->get_clock()),
  tf_listener_(tf_buffer_) {
  mask_b_ = this->declare_parameter<int>("mask_b", 4);
  mask_g_ = this->declare_parameter<int>("mask_g", 235);
  mask_r_ = this->declare_parameter<int>("mask_r", 255);
  tolerance_ = this->declare_parameter<int>("tolerance", 10);
  min_depth_m_ = this->declare_parameter<double>("min_depth_m", 0.1);
  max_depth_m_ = this->declare_parameter<double>("max_depth_m", 25.0);
  dedup_radius_m_ = this->declare_parameter<double>("dedup_radius_m", 8.0);
  min_points_ = this->declare_parameter<int>("min_points", 20);
  setup_interfaces();
}

void ObjectDetectionNode::setup_interfaces() {
  semantic_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/realsense/semantic/image_raw", rclcpp::SensorDataQoS(),
    std::bind(&ObjectDetectionNode::on_semantic, this, std::placeholders::_1));
  depth_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/realsense/depth/image", rclcpp::SensorDataQoS(),
    std::bind(&ObjectDetectionNode::on_depth, this, std::placeholders::_1));
  info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
    "/realsense/depth/camera_info", rclcpp::SensorDataQoS(),
    std::bind(&ObjectDetectionNode::on_camera_info, this, std::placeholders::_1));
  lantern_pub_ = this->create_publisher<utils::msg::LanternPoseArray>("/perception/lantern_poses", 10);
}

void ObjectDetectionNode::on_depth(const sensor_msgs::msg::Image::SharedPtr msg) {
  std::lock_guard<std::mutex> lock(data_mutex_);
  latest_depth_ = msg;
}

void ObjectDetectionNode::on_camera_info(const sensor_msgs::msg::CameraInfo::SharedPtr msg) {
  std::lock_guard<std::mutex> lock(data_mutex_);
  latest_info_ = msg;
}

bool ObjectDetectionNode::is_unique(const geometry_msgs::msg::Point & p) const {
  const double r2 = dedup_radius_m_ * dedup_radius_m_;
  for (const auto & q : detections_) {
    const double dx = p.x - q.x;
    const double dy = p.y - q.y;
    const double dz = p.z - q.z;
    if (dx * dx + dy * dy + dz * dz < r2) {
      return false;
    }
  }
  return true;
}

void ObjectDetectionNode::publish_detection(const geometry_msgs::msg::Point & p) {
  detections_.push_back(p);

  utils::msg::LanternPoseArray msg;
  msg.header.stamp = this->now();
  msg.header.frame_id = "world";
  msg.confirmed_count = static_cast<uint32_t>(detections_.size());
  msg.lanterns.reserve(detections_.size());

  for (size_t i = 0; i < detections_.size(); ++i) {
    utils::msg::LanternPose lantern;
    lantern.stamp = msg.header.stamp;
    lantern.id = static_cast<uint32_t>(i);
    lantern.pose.position = detections_[i];
    lantern.pose.orientation.w = 1.0;
    lantern.confidence = 1.0f;
    lantern.confirmed = true;
    lantern.source_frame = "world";
    msg.lanterns.push_back(lantern);
  }
  lantern_pub_->publish(msg);
}

void ObjectDetectionNode::on_semantic(const sensor_msgs::msg::Image::SharedPtr msg) {
  sensor_msgs::msg::Image::SharedPtr depth;
  sensor_msgs::msg::CameraInfo::SharedPtr info;
  {
    std::lock_guard<std::mutex> lock(data_mutex_);
    depth = latest_depth_;
    info = latest_info_;
  }

  if (!depth || !info) {
    return;
  }

  cv_bridge::CvImageConstPtr semantic_cv;
  cv_bridge::CvImageConstPtr depth_cv;
  try {
    sensor_msgs::msg::Image::ConstSharedPtr semantic_const = msg;
    sensor_msgs::msg::Image::ConstSharedPtr depth_const = depth;
    semantic_cv = cv_bridge::toCvShare(semantic_const, sensor_msgs::image_encodings::BGR8);
    depth_cv = cv_bridge::toCvShare(depth_const, sensor_msgs::image_encodings::TYPE_16UC1);
  } catch (const cv_bridge::Exception & ex) {
    RCLCPP_WARN(this->get_logger(), "object detection conversion failed: %s", ex.what());
    return;
  }

  cv::Mat mask;
  cv::inRange(
    semantic_cv->image,
    cv::Scalar(mask_b_ - tolerance_, mask_g_ - tolerance_, mask_r_ - tolerance_),
    cv::Scalar(mask_b_ + tolerance_, mask_g_ + tolerance_, mask_r_ + tolerance_),
    mask);

  if (mask.size() != depth_cv->image.size()) {
    cv::resize(mask, mask, depth_cv->image.size(), 0.0, 0.0, cv::INTER_NEAREST);
  }

  const double fx = info->k[0];
  const double fy = info->k[4];
  const double cx = info->k[2];
  const double cy = info->k[5];
  if (fx <= 0.0 || fy <= 0.0) {
    return;
  }

  double sx = 0.0;
  double sy = 0.0;
  double sz = 0.0;
  int n = 0;
  for (int v = 0; v < mask.rows; ++v) {
    const auto * mrow = mask.ptr<uint8_t>(v);
    const auto * drow = depth_cv->image.ptr<uint16_t>(v);
    for (int u = 0; u < mask.cols; ++u) {
      if (mrow[u] == 0) {
        continue;
      }
      const uint16_t dmm = drow[u];
      if (dmm == 0) {
        continue;
      }
      const double z = static_cast<double>(dmm) * 1e-3;
      if (z < min_depth_m_ || z > max_depth_m_) {
        continue;
      }
      const double x = (static_cast<double>(u) - cx) * z / fx;
      const double y = (static_cast<double>(v) - cy) * z / fy;
      sx += x;
      sy += y;
      sz += z;
      ++n;
    }
  }

  if (n < min_points_) {
    return;
  }

  geometry_msgs::msg::PointStamped camera_point;
  camera_point.header.frame_id =
    depth->header.frame_id.empty() ? info->header.frame_id : depth->header.frame_id;
  camera_point.header.stamp.sec = 0;
  camera_point.header.stamp.nanosec = 0;
  camera_point.point.x = sx / static_cast<double>(n);
  camera_point.point.y = sy / static_cast<double>(n);
  camera_point.point.z = sz / static_cast<double>(n);

  geometry_msgs::msg::PointStamped world_point;
  try {
    world_point = tf_buffer_.transform(camera_point, "world", tf2::durationFromSec(0.1));
  } catch (const tf2::TransformException &) {
    return;
  }

  if (!is_unique(world_point.point)) {
    return;
  }
  publish_detection(world_point.point);
}

}  // namespace perception_pipeline

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<perception_pipeline::ObjectDetectionNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
