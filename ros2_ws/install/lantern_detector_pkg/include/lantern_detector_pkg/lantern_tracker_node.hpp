#ifndef LANTERN_DETECTOR_PKG__LANTERN_TRACKER_NODE_HPP_
#define LANTERN_DETECTOR_PKG__LANTERN_TRACKER_NODE_HPP_

#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>

#include <mutex>
#include <opencv2/opencv.hpp>

#include "geometry_msgs/msg/pose_array.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/camera_info.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "statemachine_pkg/msg/answer.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "visualization_msgs/msg/marker_array.hpp"

namespace lantern_detector {

/**
 * @brief 表示一个检测到的灯笼，并维护其位置的滑动平均值。
 */
struct Lantern {
    geometry_msgs::msg::Point position; /**< 世界坐标系下的当前平均位置（米）。 */
    int count{0};                       /**< 该灯笼被观测到的次数。 */
};

/**
 * @brief 融合语义相机与深度图像，在世界坐标系下检测并跟踪灯笼位置的 ROS2 节点。
 *
 * 该节点订阅语义图像和深度图像，执行近似时间同步，将有效深度像素投影到
 * 三维坐标，并对观测结果进行时序平滑。检测结果会以 PoseArray、计数和
 * 可视化标记的形式发布，同时周期性发送心跳消息。
 */
class LanternDetectorNode : public rclcpp::Node {
   public:
    /**
     * @brief 构造一个新的 LanternDetectorNode 对象。
     *
     * @param options 组件化基础设施传入的 NodeOptions。
     */
    explicit LanternDetectorNode(const rclcpp::NodeOptions& options);

   private:
    /**
     * @brief 接收到同步后的语义图像和深度图像时触发的回调。
     *
     * @param semantic_msg 包含灯笼标签的语义相机图像。
     * @param depth_msg 与语义视角对应的深度图像。
     */
    void synchronized_callback(const sensor_msgs::msg::Image::ConstSharedPtr& semantic_msg,
                               const sensor_msgs::msg::Image::ConstSharedPtr& depth_msg);

    /**
     * @brief 用新观测更新灯笼列表。
     *
     * 如果新位置与已有灯笼足够接近，则将其纳入平均值；否则新增一个灯笼条目。
     *
     * @param new_position 新检测到的灯笼在世界坐标系下的位置（米）。
     */
    void update_lanterns(const geometry_msgs::msg::Point& new_position);

    /**
     * @brief 将当前灯笼检测结果、计数和可视化标记发布到各自话题。
     *
     * 只有观测次数不少于 @c min_sightings_ 的灯笼才会被发布。
     */
    void publish_lanterns();

    /**
     * @brief 发布节点仍在运行的心跳消息。
     */
    void publish_heartbeat();

    // 配置参数
    std::string world_frame_;          /**< 输出位姿使用的目标世界坐标系。 */
    double distance_threshold_m_;      /**< 灯笼合并距离阈值（米）。 */
    double min_depth_m_;               /**< 有效深度的最小值（米）。 */
    double max_depth_m_;               /**< 有效深度的最大值（米）。 */
    int min_sightings_;                /**< 发布灯笼前所需的最小观测次数。 */
    double marker_scale_m_;            /**< 可视化标记直径（米）。 */
    std::vector<double> marker_color_; /**< 标记使用的 RGBA 颜色。 */

    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;              /**< 用于 TF 查询的缓冲区。 */
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_; /**< 为 TF 缓冲区提供数据的监听器。 */

    // 语义图像和深度图像的同步订阅器
    std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> sub_semantic_filter_;
    std::shared_ptr<message_filters::Subscriber<sensor_msgs::msg::Image>> sub_depth_filter_;

    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::msg::Image, sensor_msgs::msg::Image>
        SyncPolicy;
    std::shared_ptr<message_filters::Synchronizer<SyncPolicy>> sync_; /**< 基于策略的同步器。 */

    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr
        sub_depth_info_;                                      /**< CameraInfo 订阅器。 */
    sensor_msgs::msg::CameraInfo::ConstSharedPtr depth_info_; /**< 缓存的深度相机内参。 */

    // 发布器
    rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr lantern_pub_; /**< 检测到的灯笼位姿。 */
    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr
        lantern_counts_pub_; /**< 观测计数。 */
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr
        marker_pub_;                                                            /**< 可视化标记。 */
    rclcpp::Publisher<statemachine_pkg::msg::Answer>::SharedPtr heartbeat_pub_; /**< 心跳消息。 */
    rclcpp::TimerBase::SharedPtr heartbeat_timer_; /**< 触发心跳发布的定时器。 */

    std::string heartbeat_topic_;    /**< 心跳发布话题。 */
    double heartbeat_period_s_{1.0}; /**< 心跳周期（秒）。 */

    std::vector<Lantern> detected_lanterns_; /**< 当前平滑后的灯笼检测集合。 */
};

}  // namespace lantern_detector

#endif  // LANTERN_DETECTOR_PKG__LANTERN_TRACKER_NODE_HPP_
