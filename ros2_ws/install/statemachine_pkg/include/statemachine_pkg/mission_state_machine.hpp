#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <geometry_msgs/msg/pose_array.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <memory>
#include <nav_msgs/msg/odometry.hpp>
#include <octomap_msgs/msg/octomap.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>
#include <vector>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include "statemachine_pkg/msg/answer.hpp"
#include "statemachine_pkg/msg/command.hpp"
#include "statemachine_pkg/protocol.hpp"

namespace octomap {
class OcTree;
}

/**
 * @class StateMachine
 * @brief 协调自主无人机高层任务状态机的 ROS2 节点。
 *
 * 负责管理 TAKEOFF、TRAVELLING、EXPLORING、RETURN_HOME、LAND 等状态，
 * 通过心跳检测被监控节点，并在状态切换时下发命令。
 */
class StateMachine : public rclcpp::Node {
   public:  // 状态与命令
    using MissionStates = statemachine_pkg::protocol::MissionStates;
    using Commands = statemachine_pkg::protocol::Commands;
    using AnswerStates = statemachine_pkg::protocol::AnswerStates;

   private:  // 成员变量与结构体
    /**
     * @brief 用于跟踪被监控节点心跳状态的辅助结构体。
     */
    struct NodeInfo {
        std::string node_name;                            ///< 系统中的节点名称。
        rclcpp::Time last_heartbeat{0, 0, RCL_ROS_TIME};  ///< 最近一次收到心跳的时间戳。
        bool is_alive{false};   ///< 当前是否判定该节点在线。
        bool was_alive{false};  ///< 该节点是否至少在线过一次。
        AnswerStates last_state{AnswerStates::UNKNOWN};  ///< 节点最近一次上报的状态。
    };

    MissionStates current_mission_state_{MissionStates::WAITING};  ///< 当前高层任务状态。
    rclcpp::Time state_entry_timestamp_{
        0, 0, RCL_ROS_TIME};  ///< 进入当前任务状态的时间戳。
    rclcpp::Time last_takeoff_command_timestamp_{
        0, 0, RCL_ROS_TIME};  ///< 上一次周期性下发 TAKEOFF 命令的时间戳。
    Commands last_sent_command_{Commands::NONE};  ///< 最近一次发送的命令（用于日志和逻辑判断）。

    std::vector<NodeInfo>
        monitored_nodes_;  ///< 通过心跳进行监控的外部节点集合。
    std::size_t latest_lantern_count_{
        0};  ///< 最近一次上报的去重后灯笼总数。
    std::size_t announced_lantern_count_{
        0};  ///< 已经对外播报过的唯一灯笼数量，用于避免重复打印。
    rclcpp::Time last_lantern_announce_time_{
        0, 0, RCL_ROS_TIME};  ///< 上一次灯笼摘要 topic 发布的时间。
    std::deque<std::string> pending_lantern_announcements_;  ///< 等待按冷却间隔发布的灯笼摘要队列。
    std::vector<std::size_t>
        lantern_sighting_samples_;  ///< 每个已发现灯笼的累计观测次数。
    std::vector<Eigen::Vector3d> active_checkpoint_positions_m_;  ///< 当前用于可视化和导航的航点列表（单位：米）。
    std::vector<Eigen::Vector3d> base_checkpoint_positions_m_;    ///< 配置中的静态航点列表（单位：米，不含动态起飞点）。

    bool is_checkpoint_reached_{
        false};  ///< 无人机到达当前任务航点时置为 true。
    short active_checkpoint_index_{
        -1};  ///< 当前目标航点在 active_checkpoint_positions_m_ 中的索引（-1 表示无）。
    bool has_takeoff_checkpoint_been_inserted_{
        false};  ///< 是否已在任务起始处插入一个离地 5 米的动态起飞航点。
    short active_landing_checkpoint_index_{
        -1};  ///< 动态生成的降落航点索引（-1 表示尚未生成）。

    bool has_boot_timeout_been_reported_{
        false};  ///< 防止在 WAITING 状态下重复输出启动超时日志。
    bool has_received_current_pose_{
        false};  ///< 是否至少收到过一次状态估计消息。
    bool has_received_octomap_{
        false};  ///< 是否至少收到过一次用于地面估计的 octomap 消息。
    geometry_msgs::msg::Point current_position_m_;  ///< 当前状态估计给出的无人机位置（单位：米）。
    std::string current_pose_frame_id_{
        "world"};  ///< 当前位姿和轨迹可视化使用的参考坐标系。
    std::vector<geometry_msgs::msg::Point>
        flight_path_points_;  ///< 用于轨迹折线可视化的历史位置序列。
    bool is_planner_exploration_completed_{
        false};  ///< 路径规划器是否上报探索已完成。
    bool is_planner_return_home_completed_{
        false};  ///< 路径规划器是否上报返航已完成。
    std::shared_ptr<octomap::OcTree>
        latest_octomap_octree_;  ///< 缓存的八叉树，用于降落时基于地图估计地面高度。
    rclcpp::TimerBase::SharedPtr periodic_task_timer_;  ///< 用于状态发布和心跳监控等周期任务的定时器。

   private:  // 订阅器、发布器、定时器
    // 发布器
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_state_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_lantern_summary_;
    rclcpp::Publisher<statemachine_pkg::msg::Command>::SharedPtr pub_cmd_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr pub_viz_checkpoint_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pub_viz_path_flight_;

    // 订阅器
    rclcpp::Subscription<statemachine_pkg::msg::Answer>::SharedPtr sub_heartbeat_;
    rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr sub_lantern_detections_;
    rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr sub_lantern_counts_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_current_state_est_;
    rclcpp::Subscription<octomap_msgs::msg::Octomap>::SharedPtr sub_octomap_;

   private:  // 参数
    // 列表
    // 节点
    std::vector<std::string> node_list_;  // 需要监控的节点列表
    // 航点
    std::vector<double> checkpoint_list_;  // 航点位置的扁平数组
                                           // 形式为 [x1, y1, z1, x2, y2, z2, ...]

    // 定时周期
    double pub_state_loop_sec_;             // 状态发布周期
    double alive_tol_sec_;                  // 超过该时间未收到心跳则判定节点离线
    double boot_timeout_sec_;               // 在 WAITING/BOOT 阶段允许等待节点启动的最长时间
    double takeoff_cmd_retry_sec_;          // 处于 TAKEOFF 状态时，TAKEOFF 命令的重发周期
    double checkpoint_reach_dist_m_;        // 判定到达航点的距离阈值
    double path_sample_dist_m_;             // 轨迹采样点之间的最小距离
    double landing_xy_radius_m_;            // 局部地面估计的 XY 搜索半径
    double landing_xy_radius_max_m_;        // 自适应地面估计的最大 XY 搜索半径
    double landing_xy_radius_increment_m_;  // 自适应地面估计的搜索半径增量
    double landing_clearance_m_;            // 降落目标点相对地面的安全高度
    double landing_probe_depth_m_;          // 地面估计时向下射线探测的最大深度
    int landing_min_hit_count_;             // 有效地面命中的最小数量
    double landing_min_hit_fraction_;       // 采样圆盘内命中比例的最小值
    bool landing_use_start_fallback_;       // 地图地面估计失败时，是否回退到起点附近方案

    // 话题
    // 状态相关
    std::string topic_state_;              // 发布状态机状态
    std::string topic_cmd_;                // 向其他节点发布命令
    std::string topic_heartbeat_;          // 订阅心跳以检查节点是否离线
    std::string topic_current_state_est_;  // 订阅当前状态估计
    std::string topic_octomap_;            // 订阅 octomap 地图数据

    // 灯笼相关
    std::string topic_lantern_detections_;  // 订阅灯笼检测结果
    std::string topic_lantern_counts_;      // 订阅与检测结果对齐的计数信息
    std::string topic_lantern_summary_;     // 发布新灯发现摘要
    double lantern_announce_cooldown_sec_{2.0};  // 两次灯笼播报之间的最小间隔

    // 可视化
    std::string topic_viz_checkpoint;   // 发布航点可视化
    std::string topic_viz_path_flight;  // 发布飞行轨迹可视化

    // 日志
    std::string lantern_log_path_;  // 灯笼检测日志文件路径
                                    // （CSV 格式）
    std::string event_log_path_;    // 状态机事件日志文件路径
                                    // （纯文本格式）
    std::string octomap_log_path_;  // 最终 octomap 的保存路径

    // 节点角色索引（对应 node_list_ 中的条目）
    int node_controller_index_{-1};  // 控制器节点索引
    int node_waypoint_index_{-1};    // 航点节点索引
    int node_planner_index_{-1};     // 路径规划节点索引

   public:  // 构造函数与方法
    /**
     * @brief StateMachine 节点构造函数。
     */
    StateMachine();

    /**
     * @brief StateMachine 节点析构函数。
     */
    ~StateMachine();

    /**
     * @brief 将当前状态格式化为字符串并发布到 `/state` 话题。
     */
    void publishState();

    /**
     * @brief 切换任务状态，记录进入时间，并输出状态切换日志。
     * @param target_mission_state 目标任务状态。
     * @param state_change_reason 用于记录的可读切换原因。
     */
    void changeState(MissionStates target_mission_state, const std::string& state_change_reason);

    /**
     * @brief 向 ROS 2 图中的指定节点下发高层命令。
     * @param receiver_node_name 目标节点的精确名称。
     * @param command_enum 要发送的命令。
     */
    void sendCommand(std::string receiver_node_name, Commands command_enum);

    /**
     * @brief 向指定节点下发命令，并附带一个航点目标。
     * @param receiver_node_name 目标节点的精确名称。
     * @param command_enum 要发送的命令。
     * @param target_position_m 世界坐标系下的三维目标点。
     */
    void sendCommandWithTarget(const std::string& receiver_node_name, Commands command_enum,
                               const geometry_msgs::msg::Point& target_position_m);

    /**
     * @brief 处理外部节点的心跳回复并维护健康状态。
     * @param shared_answer_msg 输入协议消息的指针。
     */
    void handleAnswer(const statemachine_pkg::msg::Answer::SharedPtr shared_answer_msg);

    /**
     * @brief 周期性处理灯笼检测结果的回调函数。
     * @param pose_array_msg 当前视野内灯笼位姿数组。
     */
    void onLanternDetections(const geometry_msgs::msg::PoseArray::SharedPtr pose_array_msg);

    /**
     * @brief 更新每个已检测灯笼的置信计数。
     * @param int_array_msg 检测器对每条轨迹上报的观测次数。
     */
    void onLanternCounts(const std_msgs::msg::Int32MultiArray::SharedPtr int_array_msg);

    /**
     * @brief 缓存最近一次 Octomap，用于降落地面估计。
     * @param octomap_msg 二进制编码的 Octomap 数据。
     */
    void onOctomap(const octomap_msgs::msg::Octomap::SharedPtr octomap_msg);

    /**
     * @brief 接收当前无人机状态估计并更新本地位置。
     * @param odometry_msg 包含当前位姿和坐标系信息的里程计消息。
     */
    void onCurrentStateEst(const nav_msgs::msg::Odometry::SharedPtr odometry_msg);

    /**
     * @brief 状态机逻辑的周期性回调（频率由 pub_state_loop_sec_ 决定）。
     */
    void onTimer();

   private:  // 辅助方法
    /**
     * @brief 检查配置中所有预期节点是否都在上报心跳。
     * 当所有必需节点健康时，触发任务状态推进。
     */
    void checkHeartbeats();

    /**
     * @brief 计算到当前活动航点的距离，并更新到达标志。
     */
    void checkCheckpoints();

    /**
     * @brief 初始化时，尝试在无人机当前起点上方插入一个 5 米起飞航点。
     */
    void tryInsertStartCheckpoint();

    /**
     * @brief 向当前 Octomap 下方做射线检测以寻找可降落平面。
     * @param calculated_ground_z_m 输出参数，返回估计得到的地面高度（米）。
     * @return bool 若在无人机下方找到有效地面则返回 true。
     */
    bool estimateGroundHeight(double& calculated_ground_z_m) const;

    /**
     * @brief 基于局部地形或起点回退方案生成安全降落航点。
     * @param landing_target_out 输出的降落目标点坐标。
     * @return bool 若成功计算出有效降落点则返回 true。
     */
    bool prepareLandingCheckpoint(geometry_msgs::msg::Point& landing_target_out);

    /**
     * @brief 处理状态切换和目标到达标志带来的附加逻辑。
     */
    void handleFlagEvents();

    /**
     * @brief 发布表示无人机飞行轨迹的 LINE_STRIP 标记。
     */
    void publishPathViz();

    /**
     * @brief 发布表示任务航点的 SPHERE 标记。
     */
    void publishCheckpointViz();

    /**
     * @brief 将节点角色索引映射为配置中的字符串名称。
     * @param list_index 在 node_list_ 参数中的位置。
     * @return std::string 解析后的名称；若索引无效则返回空字符串。
     */
    std::string nodeNameByIndex(int list_index) const;

   private:  // 日志
    /**
     * @brief 将事件字符串写入节点配置的文本日志文件。
     * @param event_message 事件的文字描述。
     */
    void logEvent(const std::string& event_message);

    /**
     * @brief 记录已发送命令，并持久化到事件日志中。
     * @param receiver_node_name 命令接收目标。
     * @param command_enum 当前下发的命令。
     */
    void logCommand(const std::string& receiver_node_name, Commands command_enum);

    /**
     * @brief 按当前整帧检测结果重写灯笼 CSV 日志，避免保留旧轮次残留行。
     * @param pose_array_msg 当前检测帧中的灯笼位姿数组。
     */
    void writeLanternSnapshotLog(const geometry_msgs::msg::PoseArray& pose_array_msg);
    void publishPendingLanternAnnouncement();

   private:  // 字符串辅助函数
    /**
     * @brief 将 MissionStates 枚举转换为可读字符串。
     * @param current_state 要转换的枚举值。
     * @return std::string 状态名称。
     */
    static std::string toString(MissionStates current_state);

    /**
     * @brief 将 Commands 枚举转换为可读字符串。
     * @param active_command 要转换的枚举值。
     * @return std::string 命令名称。
     */
    static std::string toString(Commands active_command);
};
