#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <sstream>
#include <vector>

#include <geometry_msgs/msg/transform_stamped.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <tf2/LinearMath/Transform.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include "mapping/voxel_grid_mapper_node.hpp"

namespace mapping {

namespace {

constexpr int64_t kVoxelBias = 1 << 20;
constexpr int64_t kVoxelMask = (1 << 21) - 1;

inline int64_t pack_key(int x, int y, int z) {
  const int64_t xx = static_cast<int64_t>(x) + kVoxelBias;
  const int64_t yy = static_cast<int64_t>(y) + kVoxelBias;
  const int64_t zz = static_cast<int64_t>(z) + kVoxelBias;
  return (xx << 42) | (yy << 21) | zz;
}

inline VoxelGridMapperNode::VoxelCoord unpack_key(int64_t key) {
  VoxelGridMapperNode::VoxelCoord out;
  out.x = static_cast<int>((key >> 42) & kVoxelMask) - static_cast<int>(kVoxelBias);
  out.y = static_cast<int>((key >> 21) & kVoxelMask) - static_cast<int>(kVoxelBias);
  out.z = static_cast<int>(key & kVoxelMask) - static_cast<int>(kVoxelBias);
  return out;
}

inline double dist3(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b) {
  const double dx = a.x - b.x;
  const double dy = a.y - b.y;
  const double dz = a.z - b.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

}  // namespace

VoxelGridMapperNode::VoxelGridMapperNode()
: Node("voxel_grid_mapper_node"),
  tf_buffer_(this->get_clock()),
  tf_listener_(tf_buffer_) {
  resolution_ = this->declare_parameter<double>("resolution", 0.5);
  frame_id_ = this->declare_parameter<std::string>("frame_id", "world");
  point_stride_ = this->declare_parameter<int>("point_stride", 8);
  serialization_voxel_limit_ = this->declare_parameter<int>("serialization_voxel_limit", 150000);
  min_frontier_altitude_m_ = this->declare_parameter<double>("min_frontier_altitude_m", 2.0);
  max_frontier_altitude_m_ = this->declare_parameter<double>("max_frontier_altitude_m", 35.0);
  frontier_republish_distance_m_ = this->declare_parameter<double>("frontier_republish_distance_m", 3.0);
  frontier_x_bias_ = this->declare_parameter<double>("frontier_x_bias", 0.35);
  setup_interfaces();
}

void VoxelGridMapperNode::setup_interfaces() {
  odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
    "/current_state_est", 10,
    std::bind(&VoxelGridMapperNode::on_odometry, this, std::placeholders::_1));

  cloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
    "/mapping/pointcloud_in", rclcpp::SensorDataQoS(),
    std::bind(&VoxelGridMapperNode::on_pointcloud, this, std::placeholders::_1));

  map_pub_ = this->create_publisher<utils::msg::GlobalMap>("/mapping/global_map_raw", 10);
  frontier_pub_ = this->create_publisher<geometry_msgs::msg::Point>("/planning/frontier_goal", 10);
  stats_pub_ = this->create_publisher<std_msgs::msg::String>("/mapping/status", 10);

  timer_ = this->create_wall_timer(
    std::chrono::seconds(1),
    std::bind(&VoxelGridMapperNode::publish_map_summary, this));
}

void VoxelGridMapperNode::on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg) {
  have_odom_ = true;
  current_position_ = msg->pose.pose.position;
}

VoxelGridMapperNode::VoxelCoord VoxelGridMapperNode::world_to_voxel(
  double x, double y, double z) const
{
  VoxelCoord out;
  out.x = static_cast<int>(std::floor(x / resolution_));
  out.y = static_cast<int>(std::floor(y / resolution_));
  out.z = static_cast<int>(std::floor(z / resolution_));
  return out;
}

geometry_msgs::msg::Point VoxelGridMapperNode::voxel_to_world_center(const VoxelCoord & voxel) const {
  geometry_msgs::msg::Point p;
  p.x = (static_cast<double>(voxel.x) + 0.5) * resolution_;
  p.y = (static_cast<double>(voxel.y) + 0.5) * resolution_;
  p.z = (static_cast<double>(voxel.z) + 0.5) * resolution_;
  return p;
}

void VoxelGridMapperNode::mark_free_ray(const VoxelCoord & from, const VoxelCoord & to) {
  const int dx = to.x - from.x;
  const int dy = to.y - from.y;
  const int dz = to.z - from.z;
  const int steps = std::max({std::abs(dx), std::abs(dy), std::abs(dz)});

  if (steps <= 1) {
    return;
  }

  for (int i = 0; i < steps; ++i) {
    const double t = static_cast<double>(i) / static_cast<double>(steps);
    const int vx = static_cast<int>(std::round(static_cast<double>(from.x) + t * static_cast<double>(dx)));
    const int vy = static_cast<int>(std::round(static_cast<double>(from.y) + t * static_cast<double>(dy)));
    const int vz = static_cast<int>(std::round(static_cast<double>(from.z) + t * static_cast<double>(dz)));
    const int64_t key = pack_key(vx, vy, vz);
    if (occupied_voxels_.find(key) == occupied_voxels_.end()) {
      free_voxels_.insert(key);
    }
  }
}

void VoxelGridMapperNode::on_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
  if (msg->data.empty()) {
    return;
  }

  geometry_msgs::msg::TransformStamped tf_msg;
  bool have_tf = false;
  try {
    tf_msg = tf_buffer_.lookupTransform(frame_id_, msg->header.frame_id, rclcpp::Time(msg->header.stamp));
    have_tf = true;
  } catch (const tf2::TransformException &) {
    try {
      tf_msg = tf_buffer_.lookupTransform(frame_id_, msg->header.frame_id, tf2::TimePointZero);
      have_tf = true;
    } catch (const tf2::TransformException & ex) {
      RCLCPP_WARN_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "mapping: cannot transform %s->%s (%s); using cloud frame coordinates",
        msg->header.frame_id.c_str(), frame_id_.c_str(), ex.what());
    }
  }

  tf2::Transform tf_world_sensor;
  tf_world_sensor.setIdentity();
  geometry_msgs::msg::Point sensor_origin_world;
  if (have_tf) {
    tf2::fromMsg(tf_msg.transform, tf_world_sensor);
    sensor_origin_world.x = tf_msg.transform.translation.x;
    sensor_origin_world.y = tf_msg.transform.translation.y;
    sensor_origin_world.z = tf_msg.transform.translation.z;
  } else {
    sensor_origin_world.x = 0.0;
    sensor_origin_world.y = 0.0;
    sensor_origin_world.z = 0.0;
  }
  const VoxelCoord sensor_voxel =
    world_to_voxel(sensor_origin_world.x, sensor_origin_world.y, sensor_origin_world.z);

  sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x");
  sensor_msgs::PointCloud2ConstIterator<float> iter_y(*msg, "y");
  sensor_msgs::PointCloud2ConstIterator<float> iter_z(*msg, "z");

  const size_t count = static_cast<size_t>(msg->width) * static_cast<size_t>(msg->height);
  const int stride = std::max(1, point_stride_);
  for (size_t i = 0; i < count; ++i, ++iter_x, ++iter_y, ++iter_z) {
    if ((i % static_cast<size_t>(stride)) != 0u) {
      continue;
    }

    double x = static_cast<double>(*iter_x);
    double y = static_cast<double>(*iter_y);
    double z = static_cast<double>(*iter_z);
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
      continue;
    }

    if (have_tf) {
      const tf2::Vector3 p_local(x, y, z);
      const tf2::Vector3 p_world = tf_world_sensor * p_local;
      x = p_world.x();
      y = p_world.y();
      z = p_world.z();
    }

    const VoxelCoord hit_voxel = world_to_voxel(x, y, z);
    mark_free_ray(sensor_voxel, hit_voxel);
    const int64_t hit_key = pack_key(hit_voxel.x, hit_voxel.y, hit_voxel.z);
    occupied_voxels_.insert(hit_key);
    free_voxels_.erase(hit_key);
  }
}

std::optional<VoxelGridMapperNode::VoxelCoord> VoxelGridMapperNode::find_frontier_voxel() const {
  if (!have_odom_ || free_voxels_.empty()) {
    return std::nullopt;
  }

  double best_score = -std::numeric_limits<double>::infinity();
  std::optional<VoxelCoord> best;
  const std::array<VoxelCoord, 6> kAxisNeighbors{
    VoxelCoord{1, 0, 0}, VoxelCoord{-1, 0, 0}, VoxelCoord{0, 1, 0},
    VoxelCoord{0, -1, 0}, VoxelCoord{0, 0, 1}, VoxelCoord{0, 0, -1}};

  for (const int64_t key : free_voxels_) {
    const VoxelCoord v = unpack_key(key);
    const geometry_msgs::msg::Point p = voxel_to_world_center(v);
    if (p.z < min_frontier_altitude_m_ || p.z > max_frontier_altitude_m_) {
      continue;
    }

    const double d = dist3(p, current_position_);
    if (d < 3.0) {
      continue;
    }

    bool has_unknown_neighbor = false;
    for (const auto & nb : kAxisNeighbors) {
      const int64_t nk = pack_key(v.x + nb.x, v.y + nb.y, v.z + nb.z);
      if (
        occupied_voxels_.find(nk) == occupied_voxels_.end() &&
        free_voxels_.find(nk) == free_voxels_.end())
      {
        has_unknown_neighbor = true;
      }
    }

    if (!has_unknown_neighbor) {
      continue;
    }

    // Encourage cave progression (negative x) while still favoring exploration distance.
    const double x_progress = std::max(0.0, current_position_.x - p.x);
    const double score = d + frontier_x_bias_ * x_progress;
    if (score > best_score) {
      best_score = score;
      best = v;
    }
  }

  return best;
}

void VoxelGridMapperNode::publish_map_summary() {
  utils::msg::GlobalMap map_msg;
  map_msg.header.stamp = this->now();
  map_msg.header.frame_id = frame_id_;
  map_msg.map_type = "voxel_grid";
  map_msg.frame_id = frame_id_;
  map_msg.resolution = static_cast<float>(resolution_);
  map_msg.occupied_voxels = static_cast<uint32_t>(occupied_voxels_.size());
  map_msg.free_voxels = static_cast<uint32_t>(free_voxels_.size());
  map_msg.unknown_voxels = 0u;
  map_msg.explored_volume_m3 = static_cast<float>(
    (occupied_voxels_.size() + free_voxels_.size()) * resolution_ * resolution_ * resolution_);
  map_msg.storage_path = "";
  map_msg.valid = !occupied_voxels_.empty() || !free_voxels_.empty();

  auto append_voxels = [this](
      const std::unordered_set<int64_t> & src,
      std::vector<int32_t> & ix, std::vector<int32_t> & iy, std::vector<int32_t> & iz) {
      const size_t n = std::min(src.size(), static_cast<size_t>(std::max(1, serialization_voxel_limit_)));
      ix.reserve(n);
      iy.reserve(n);
      iz.reserve(n);
      size_t i = 0;
      for (const int64_t key : src) {
        if (i >= n) {
          break;
        }
        const VoxelCoord v = unpack_key(key);
        ix.push_back(v.x);
        iy.push_back(v.y);
        iz.push_back(v.z);
        ++i;
      }
    };

  append_voxels(
    occupied_voxels_, map_msg.occupied_ix, map_msg.occupied_iy, map_msg.occupied_iz);
  append_voxels(
    free_voxels_, map_msg.free_ix, map_msg.free_iy, map_msg.free_iz);

  const std::optional<VoxelCoord> frontier_voxel = find_frontier_voxel();
  if (frontier_voxel.has_value()) {
    const geometry_msgs::msg::Point frontier = voxel_to_world_center(frontier_voxel.value());
    map_msg.frontier_goal = frontier;
    map_msg.frontier_goal_valid = true;

    if (
      !last_frontier_goal_.has_value() ||
      dist3(last_frontier_goal_.value(), frontier) > frontier_republish_distance_m_)
    {
      frontier_pub_->publish(frontier);
      last_frontier_goal_ = frontier;
    }
  } else {
    map_msg.frontier_goal_valid = false;
  }

  map_pub_->publish(map_msg);

  std_msgs::msg::String status;
  std::ostringstream ss;
  ss << "occupied=" << occupied_voxels_.size()
     << ", free=" << free_voxels_.size()
     << ", explored_m3=" << map_msg.explored_volume_m3
     << ", frontier=" << (map_msg.frontier_goal_valid ? "yes" : "no");
  status.data = ss.str();
  stats_pub_->publish(status);
}

}  // namespace mapping

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<mapping::VoxelGridMapperNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
