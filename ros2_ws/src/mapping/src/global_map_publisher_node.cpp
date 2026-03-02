#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <ament_index_cpp/get_package_share_directory.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>

#include "mapping/global_map_publisher_node.hpp"

namespace mapping {

GlobalMapPublisherNode::GlobalMapPublisherNode()
: Node("global_map_publisher_node") {
  // Derive workspace root from the install share dir:
  // <ws>/install/mapping/share/mapping  →  4 levels up  →  <ws>
  std::filesystem::path share_dir =
    ament_index_cpp::get_package_share_directory("mapping");
  output_dir_ = (share_dir.parent_path().parent_path()
                           .parent_path().parent_path() / "src" / "output").string();
  std::filesystem::create_directories(output_dir_);
  RCLCPP_INFO(this->get_logger(), "Output directory: %s", output_dir_.c_str());
  setup_interfaces();
}

void GlobalMapPublisherNode::setup_interfaces() {
  map_sub_ = this->create_subscription<utils::msg::GlobalMap>(
    "/mapping/global_map_raw", 10,
    std::bind(&GlobalMapPublisherNode::on_map_raw, this, std::placeholders::_1));

  mission_state_sub_ = this->create_subscription<std_msgs::msg::String>(
    "/mission/state", 10,
    std::bind(&GlobalMapPublisherNode::on_mission_state, this, std::placeholders::_1));

  lantern_sub_ = this->create_subscription<utils::msg::LanternPoseArray>(
    "/perception/lantern_poses", 10,
    std::bind(&GlobalMapPublisherNode::on_lantern_poses, this, std::placeholders::_1));

  legacy_lantern_sub_ = this->create_subscription<geometry_msgs::msg::PoseArray>(
    "/detected_lanterns", 10,
    std::bind(&GlobalMapPublisherNode::on_legacy_lantern_poses, this, std::placeholders::_1));

  map_pub_ = this->create_publisher<utils::msg::GlobalMap>("/mapping/global_map", 10);
  cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/mapping/occupied_cloud", 10);
  frontier_marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
    "/mapping/frontier_marker", 10);
  status_pub_ = this->create_publisher<std_msgs::msg::String>("/mapping/status", 10);

  save_map_srv_ = this->create_service<utils::srv::SaveMap>(
    "/mapping/save_map",
    std::bind(
      &GlobalMapPublisherNode::on_save_map, this,
      std::placeholders::_1, std::placeholders::_2));
}

void GlobalMapPublisherNode::on_map_raw(const utils::msg::GlobalMap::SharedPtr msg) {
  latest_map_ = *msg;
  has_map_ = true;
  map_pub_->publish(*msg);
  publish_visualization(*msg);
}

void GlobalMapPublisherNode::on_mission_state(const std_msgs::msg::String::SharedPtr msg) {
  if ((msg->data == "COMPLETE" || msg->data == "LAND") && !results_saved_) {
    auto_save_results();
  }
}

void GlobalMapPublisherNode::on_lantern_poses(const utils::msg::LanternPoseArray::SharedPtr msg) {
  latest_lanterns_ = *msg;
}

void GlobalMapPublisherNode::on_legacy_lantern_poses(
  const geometry_msgs::msg::PoseArray::SharedPtr msg)
{
  if (latest_lanterns_.confirmed_count >= msg->poses.size()) {
    return;
  }

  utils::msg::LanternPoseArray converted;
  converted.header = msg->header;
  converted.confirmed_count = static_cast<uint32_t>(msg->poses.size());
  converted.lanterns.reserve(msg->poses.size());
  for (size_t i = 0; i < msg->poses.size(); ++i) {
    utils::msg::LanternPose lantern;
    lantern.stamp = converted.header.stamp;
    lantern.id = static_cast<uint32_t>(i);
    lantern.pose = msg->poses[i];
    lantern.confidence = 1.0f;
    lantern.confirmed = true;
    lantern.source_frame = converted.header.frame_id.empty() ? "world" : converted.header.frame_id;
    converted.lanterns.push_back(lantern);
  }
  latest_lanterns_ = converted;
}

// ---------------------------------------------------------------------------
// PLY writer helper — height-coloured occupied voxel point cloud
// ---------------------------------------------------------------------------
static bool write_ply(
  const std::string & path,
  const utils::msg::GlobalMap & map)
{
  const size_t n = map.occupied_ix.size();
  if (n == 0) {
    return false;
  }

  const double res = map.resolution > 1e-6f
    ? static_cast<double>(map.resolution) : 0.5;

  // Compute z range for height-based colouring.
  double z_min =  1e9;
  double z_max = -1e9;
  for (size_t i = 0; i < n; ++i) {
    const double z = (map.occupied_iz[i] + 0.5) * res;
    if (z < z_min) { z_min = z; }
    if (z > z_max) { z_max = z; }
  }
  const double z_range = (z_max > z_min) ? (z_max - z_min) : 1.0;

  std::ofstream out(path);
  if (!out.is_open()) {
    return false;
  }

  // PLY ASCII header
  out << "ply\n"
      << "format ascii 1.0\n"
      << "element vertex " << n << "\n"
      << "property float x\n"
      << "property float y\n"
      << "property float z\n"
      << "property uchar red\n"
      << "property uchar green\n"
      << "property uchar blue\n"
      << "end_header\n";

  for (size_t i = 0; i < n; ++i) {
    const double x = (map.occupied_ix[i] + 0.5) * res;
    const double y = (map.occupied_iy[i] + 0.5) * res;
    const double z = (map.occupied_iz[i] + 0.5) * res;

    // Viridis-like height gradient: low=dark-blue, mid=teal/green, high=yellow
    const double t = (z - z_min) / z_range;  // 0..1
    uint8_t r, g, b;
    if (t < 0.25) {
      const double s = t / 0.25;
      r = 68;
      g = static_cast<uint8_t>(1   + s * (86  - 1));
      b = static_cast<uint8_t>(84  + s * (168 - 84));
    } else if (t < 0.5) {
      const double s = (t - 0.25) / 0.25;
      r = static_cast<uint8_t>(68  + s * (33  - 68));
      g = static_cast<uint8_t>(86  + s * (145 - 86));
      b = static_cast<uint8_t>(168 + s * (140 - 168));
    } else if (t < 0.75) {
      const double s = (t - 0.5) / 0.25;
      r = static_cast<uint8_t>(33  + s * (94  - 33));
      g = static_cast<uint8_t>(145 + s * (201 - 145));
      b = static_cast<uint8_t>(140 + s * (98  - 140));
    } else {
      const double s = (t - 0.75) / 0.25;
      r = static_cast<uint8_t>(94  + s * (253 - 94));
      g = static_cast<uint8_t>(201 + s * (231 - 201));
      b = static_cast<uint8_t>(98  + s * (37  - 98));
    }

    out << x << " " << y << " " << z
        << " " << static_cast<int>(r)
        << " " << static_cast<int>(g)
        << " " << static_cast<int>(b)
        << "\n";
  }

  return true;
}

void GlobalMapPublisherNode::auto_save_results() {
  results_saved_ = true;

  // Build timestamp string
  const std::time_t t = std::time(nullptr);
  char ts[32];
  std::strftime(ts, sizeof(ts), "%Y%m%d_%H%M%S", std::localtime(&t));
  const std::string base = output_dir_ + "/mission_" + ts;

  // --- Save voxel map as PLY ---
  const std::string map_path = base + "_map.ply";
  if (has_map_) {
    if (write_ply(map_path, latest_map_)) {
      RCLCPP_INFO(this->get_logger(), "Map saved → %s  (%zu voxels)",
        map_path.c_str(), latest_map_.occupied_ix.size());
    } else {
      RCLCPP_WARN(this->get_logger(), "Failed to write PLY to %s", map_path.c_str());
    }
  }

  // --- Save lantern positions ---
  const std::string lantern_path = base + "_lanterns.csv";
  std::ofstream lan_out(lantern_path);
  if (lan_out.is_open()) {
    lan_out << "id,x_m,y_m,z_m\n";
    for (size_t i = 0; i < latest_lanterns_.lanterns.size(); ++i) {
      const auto & p = latest_lanterns_.lanterns[i].pose.position;
      lan_out << i << "," << p.x << "," << p.y << "," << p.z << "\n";
    }
    lan_out.close();
    RCLCPP_INFO(this->get_logger(), "Lanterns saved → %s  (%u confirmed)",
      lantern_path.c_str(), latest_lanterns_.confirmed_count);
  }

  // --- Save mission summary ---
  const std::string summary_path = base + "_summary.txt";
  std::ofstream sum_out(summary_path);
  if (sum_out.is_open()) {
    sum_out << "=== Mission Results ===\n";
    sum_out << "timestamp: " << ts << "\n";
    sum_out << "occupied_voxels: " << latest_map_.occupied_voxels << "\n";
    sum_out << "free_voxels: " << latest_map_.free_voxels << "\n";
    sum_out << "explored_volume_m3: " << latest_map_.explored_volume_m3 << "\n";
    sum_out << "lanterns_confirmed: " << latest_lanterns_.confirmed_count << "\n";
    for (size_t i = 0; i < latest_lanterns_.lanterns.size(); ++i) {
      const auto & p = latest_lanterns_.lanterns[i].pose.position;
      sum_out << "  lantern[" << i << "]: ("
              << p.x << ", " << p.y << ", " << p.z << ")\n";
    }
    sum_out.close();
    RCLCPP_INFO(this->get_logger(), "Summary saved → %s", summary_path.c_str());
  }

  std_msgs::msg::String status;
  status.data = "results_saved base=" + base;
  status_pub_->publish(status);
}

void GlobalMapPublisherNode::publish_visualization(const utils::msg::GlobalMap & map) {
  // --- Occupied voxels as PointCloud2 ---
  const size_t n = map.occupied_ix.size();
  sensor_msgs::msg::PointCloud2 cloud;
  cloud.header.stamp = map.header.stamp;
  cloud.header.frame_id = map.frame_id.empty() ? "world" : map.frame_id;
  cloud.height = 1;
  cloud.width = static_cast<uint32_t>(n);
  cloud.is_dense = false;
  cloud.is_bigendian = false;

  sensor_msgs::PointCloud2Modifier modifier(cloud);
  modifier.setPointCloud2FieldsByString(1, "xyz");
  modifier.resize(n);

  sensor_msgs::PointCloud2Iterator<float> iter_x(cloud, "x");
  sensor_msgs::PointCloud2Iterator<float> iter_y(cloud, "y");
  sensor_msgs::PointCloud2Iterator<float> iter_z(cloud, "z");

  const double res = map.resolution > 1e-6f ? static_cast<double>(map.resolution) : 0.5;
  for (size_t i = 0; i < n; ++i, ++iter_x, ++iter_y, ++iter_z) {
    *iter_x = static_cast<float>((static_cast<double>(map.occupied_ix[i]) + 0.5) * res);
    *iter_y = static_cast<float>((static_cast<double>(map.occupied_iy[i]) + 0.5) * res);
    *iter_z = static_cast<float>((static_cast<double>(map.occupied_iz[i]) + 0.5) * res);
  }
  cloud_pub_->publish(cloud);

  // --- Frontier goal as a sphere marker ---
  visualization_msgs::msg::MarkerArray markers;
  if (map.frontier_goal_valid) {
    visualization_msgs::msg::Marker m;
    m.header.stamp = map.header.stamp;
    m.header.frame_id = cloud.header.frame_id;
    m.ns = "frontier";
    m.id = 0;
    m.type = visualization_msgs::msg::Marker::SPHERE;
    m.action = visualization_msgs::msg::Marker::ADD;
    m.pose.position = map.frontier_goal;
    m.pose.orientation.w = 1.0;
    m.scale.x = 2.0;
    m.scale.y = 2.0;
    m.scale.z = 2.0;
    m.color.r = 1.0f;
    m.color.g = 0.5f;
    m.color.b = 0.0f;
    m.color.a = 0.9f;
    markers.markers.push_back(m);
  }
  frontier_marker_pub_->publish(markers);
}

void GlobalMapPublisherNode::on_save_map(
  const std::shared_ptr<utils::srv::SaveMap::Request> request,
  std::shared_ptr<utils::srv::SaveMap::Response> response)
{
  if (!has_map_) {
    response->success = false;
    response->saved_path = "";
    response->message = "no map available";
    return;
  }

  std::string path = request->output_path;
  if (path.empty()) {
    path = output_dir_ + "/subterrain_global_map.ply";
  }

  // Always write PLY — it is directly viewable in CloudCompare / MeshLab / Open3D.
  if (!write_ply(path, latest_map_)) {
    response->success = false;
    response->saved_path = "";
    response->message = "failed to write PLY (empty map or bad path)";
    return;
  }

  response->success = true;
  response->saved_path = path;
  response->message = "map saved as PLY";

  std_msgs::msg::String status;
  status.data = "map saved to " + path;
  status_pub_->publish(status);
}

}  // namespace mapping

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<mapping::GlobalMapPublisherNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
