#include "detection/lantern_detector_node.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace detection {

LanternDetectorNode::LanternDetectorNode()
    : Node("lantern_detector")
{
    // Parameters
    this->declare_parameter("semantic_topic", "/Quadrotor/Sensors/SemanticCamera/image_raw");
    this->declare_parameter("depth_topic", "/realsense/depth/image");
    this->declare_parameter("depth_info_topic", "/realsense/depth/camera_info");
    this->declare_parameter("world_frame", "world");
    this->declare_parameter("distance_threshold", 1.5);
    this->declare_parameter("min_depth", 0.5);
    this->declare_parameter("max_depth", 30.0);

    semantic_topic_ = this->get_parameter("semantic_topic").as_string();
    depth_topic_ = this->get_parameter("depth_topic").as_string();
    world_frame_ = this->get_parameter("world_frame").as_string();
    distance_threshold_ = this->get_parameter("distance_threshold").as_double();
    min_depth_ = this->get_parameter("min_depth").as_double();
    max_depth_ = this->get_parameter("max_depth").as_double();

    // TF2
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    // Camera info subscription
    depth_info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
        this->get_parameter("depth_info_topic").as_string(),
        rclcpp::SensorDataQoS(),
        std::bind(&LanternDetectorNode::depth_info_callback, this, std::placeholders::_1));

    // Synchronized subscriptions
    semantic_sub_.subscribe(this, semantic_topic_, rmw_qos_profile_sensor_data);
    depth_sub_.subscribe(this, depth_topic_, rmw_qos_profile_sensor_data);

    sync_ = std::make_shared<message_filters::Synchronizer<SyncPolicy>>(
        SyncPolicy(10), semantic_sub_, depth_sub_);
    sync_->registerCallback(std::bind(&LanternDetectorNode::sync_callback, this,
                                     std::placeholders::_1, std::placeholders::_2));

    // Publishers
    pose_pub_ = this->create_publisher<geometry_msgs::msg::PoseArray>("/detected_lanterns", 10);
    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("/lantern_markers", 10);

    RCLCPP_INFO(this->get_logger(), "Lantern detector started");
    RCLCPP_INFO(this->get_logger(), "  Semantic topic: %s", semantic_topic_.c_str());
    RCLCPP_INFO(this->get_logger(), "  Depth topic: %s", depth_topic_.c_str());
    RCLCPP_INFO(this->get_logger(), "  World frame: %s", world_frame_.c_str());
}

void LanternDetectorNode::depth_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg)
{
    if (!depth_info_received_) {
        fx_ = (msg->k[0] != 0.0) ? msg->k[0] : msg->p[0];
        fy_ = (msg->k[4] != 0.0) ? msg->k[4] : msg->p[5];
        cx_ = (msg->k[2] != 0.0) ? msg->k[2] : msg->p[2];
        cy_ = (msg->k[5] != 0.0) ? msg->k[5] : msg->p[6];
        depth_info_received_ = true;
        RCLCPP_INFO(this->get_logger(), "Camera intrinsics: fx=%.1f fy=%.1f cx=%.1f cy=%.1f",
                   fx_, fy_, cx_, cy_);
    }
}

void LanternDetectorNode::sync_callback(
    const sensor_msgs::msg::Image::ConstSharedPtr& semantic_msg,
    const sensor_msgs::msg::Image::ConstSharedPtr& depth_msg)
{
    if (!depth_info_received_) {
        RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 3000,
                           "Waiting for camera info...");
        return;
    }

    try {
        cv::Mat semantic = cv_bridge::toCvShare(semantic_msg, "bgr8")->image;
        cv::Mat depth;

        if (depth_msg->encoding == "16UC1") {
            cv_bridge::toCvShare(depth_msg, "16UC1")->image.convertTo(depth, CV_32F, 0.001);
        } else {
            depth = cv_bridge::toCvShare(depth_msg, "32FC1")->image.clone();
        }

        cv::Mat gray, mask;
        cv::cvtColor(semantic, gray, cv::COLOR_BGR2GRAY);
        cv::threshold(gray, mask, 10, 255, cv::THRESH_BINARY);

        int pixel_count = cv::countNonZero(mask);
        if (pixel_count < 20) return;

        geometry_msgs::msg::Point pt_3d = compute_3d_position(
            mask, depth, semantic.size(), depth.size());

        if (std::isnan(pt_3d.x)) return;

        geometry_msgs::msg::PointStamped pt_depth;
        pt_depth.header = depth_msg->header;
        pt_depth.point = pt_3d;

        try {
            auto pt_world = tf_buffer_->transform(pt_depth, world_frame_,
                                                 tf2::durationFromSec(0.2));
            update_lanterns(pt_world.point);
            publish_lanterns();
        } catch (const tf2::TransformException& ex) {
            RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 5000,
                               "Transform failed: %s", ex.what());
        }

    } catch (const cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge error: %s", e.what());
    }
}

geometry_msgs::msg::Point LanternDetectorNode::compute_3d_position(
    const cv::Mat& mask, const cv::Mat& depth,
    const cv::Size& mask_size, const cv::Size& depth_size)
{
    geometry_msgs::msg::Point result;
    result.x = result.y = result.z = std::nan("");

    double sum_x = 0, sum_y = 0, sum_z = 0;
    int count = 0;

    for (int r = 0; r < mask.rows; ++r) {
        for (int c = 0; c < mask.cols; ++c) {
            if (mask.at<uchar>(r, c) == 0) continue;

            int dc = (mask_size.width != depth_size.width) ?
                    (c * depth_size.width / mask_size.width) : c;
            int dr = (mask_size.height != depth_size.height) ?
                    (r * depth_size.height / mask_size.height) : r;

            if (dr >= depth.rows || dc >= depth.cols) continue;

            float z = depth.at<float>(dr, dc);
            if (!std::isfinite(z) || z < min_depth_ || z > max_depth_) continue;

            double x = (dc - cx_) * z / fx_;
            double y = (dr - cy_) * z / fy_;

            sum_x += x;
            sum_y += y;
            sum_z += z;
            count++;
        }
    }

    if (count > 0) {
        result.x = sum_x / count;
        result.y = sum_y / count;
        result.z = sum_z / count;
    }

    return result;
}

void LanternDetectorNode::update_lanterns(const geometry_msgs::msg::Point& new_pos)
{
    for (auto& lantern : lanterns_) {
        double dist = std::sqrt(
            std::pow(lantern.position.x - new_pos.x, 2) +
            std::pow(lantern.position.y - new_pos.y, 2) +
            std::pow(lantern.position.z - new_pos.z, 2));

        if (dist < distance_threshold_) {
            int total = lantern.count + 1;
            lantern.position.x = (lantern.position.x * lantern.count + new_pos.x) / total;
            lantern.position.y = (lantern.position.y * lantern.count + new_pos.y) / total;
            lantern.position.z = (lantern.position.z * lantern.count + new_pos.z) / total;
            lantern.count = total;
            lantern.last_update = this->now();

            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
                "Updated lantern at [%.2f, %.2f, %.2f] (count=%d)",
                lantern.position.x, lantern.position.y, lantern.position.z, lantern.count);
            return;
        }
    }

    DetectedLantern new_lantern;
    new_lantern.position = new_pos;
    new_lantern.count = 1;
    new_lantern.last_update = this->now();
    lanterns_.push_back(new_lantern);

    RCLCPP_INFO(this->get_logger(), "New lantern at [%.2f, %.2f, %.2f] - Total: %zu",
               new_pos.x, new_pos.y, new_pos.z, lanterns_.size());
}

void LanternDetectorNode::publish_lanterns()
{
    auto stamp = this->now();

    geometry_msgs::msg::PoseArray poses;
    poses.header.stamp = stamp;
    poses.header.frame_id = world_frame_;

    visualization_msgs::msg::MarkerArray markers;

    for (size_t i = 0; i < lanterns_.size(); ++i) {
        geometry_msgs::msg::Pose pose;
        pose.position = lanterns_[i].position;
        pose.orientation.w = 1.0;
        poses.poses.push_back(pose);

        visualization_msgs::msg::Marker m;
        m.header = poses.header;
        m.ns = "lanterns";
        m.id = static_cast<int>(i);
        m.type = visualization_msgs::msg::Marker::SPHERE;
        m.action = visualization_msgs::msg::Marker::ADD;
        m.pose = pose;
        m.scale.x = m.scale.y = m.scale.z = 0.6;
        m.color.r = 1.0;
        m.color.g = 1.0;
        m.color.b = 0.0;
        m.color.a = 1.0;
        m.lifetime = rclcpp::Duration::from_seconds(5.0);
        markers.markers.push_back(m);
    }

    pose_pub_->publish(poses);
    marker_pub_->publish(markers);
}

}  // namespace detection
