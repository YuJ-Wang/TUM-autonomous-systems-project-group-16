#pragma once

#include <optional>
#include <unordered_set>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include "utils/msg/global_map.hpp"

namespace mapping {

class VoxelGridMapperNode : public rclcpp::Node {
public:
  VoxelGridMapperNode();

  struct VoxelCoord {
    int x{0};
    int y{0};
    int z{0};
  };

private:
  void setup_interfaces();
  void on_odometry(const nav_msgs::msg::Odometry::SharedPtr msg);
  void on_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void publish_map_summary();
  std::optional<VoxelCoord> find_frontier_voxel() const;
  geometry_msgs::msg::Point voxel_to_world_center(const VoxelCoord & voxel) const;
  VoxelCoord world_to_voxel(double x, double y, double z) const;
  void mark_free_ray(const VoxelCoord & from, const VoxelCoord & to);

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_sub_;
  rclcpp::Publisher<utils::msg::GlobalMap>::SharedPtr map_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr frontier_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr stats_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;

  std::unordered_set<int64_t> occupied_voxels_;
  std::unordered_set<int64_t> free_voxels_;
  double resolution_{0.5};
  std::string frame_id_{"world"};
  int point_stride_{8};
  int serialization_voxel_limit_{20000};
  double min_frontier_altitude_m_{2.0};
  double max_frontier_altitude_m_{35.0};
  double frontier_republish_distance_m_{3.0};
  double frontier_x_bias_{0.35};

  bool have_odom_{false};
  geometry_msgs::msg::Point current_position_;
  std::optional<geometry_msgs::msg::Point> last_frontier_goal_;
};

}  // namespace mapping
