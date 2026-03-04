#ifndef BASIC_WAYPOINT_PKG__PLANNER_HPP_
#define BASIC_WAYPOINT_PKG__PLANNER_HPP_

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>
#include <memory>
#include <tf2_eigen/tf2_eigen.hpp>
#include <vector>

#include "mav_msgs/conversions.hpp"
#include "mav_planning_msgs/msg/polynomial_trajectory4_d.hpp"
#include "mav_trajectory_generation/polynomial_optimization_linear.h"
#include "mav_trajectory_generation/ros_conversions.h"
#include "mav_trajectory_generation/trajectory_sampling.h"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/color_rgba.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

/**
 * @brief 为无人机生成多项式轨迹的简易规划器。
 *
 * 该规划器从里程计话题读取当前状态，并使用参数或显式提供的航点
 * 构建满足速度与加速度约束的轨迹。
 */
class BasicPlanner {
   public:
    /**
     * @brief 构造一个绑定到 ROS2 节点实例上的规划器。
     *
     * @param node ROS2 节点的共享指针，用于读取参数、创建发布器和订阅器。
     */
    explicit BasicPlanner(const rclcpp::Node::SharedPtr& node);

    /**
     * @brief 里程计回调，用于更新规划器内部状态。
     *
     * @param odom 输入里程计消息的指针。
     */
    void uavOdomCallback(const nav_msgs::msg::Odometry::SharedPtr odom);

    /**
     * @brief 设置轨迹规划的最大平移速度。
     *
     * @param max_speed_mps 最大速度，单位为米每秒（m/s）。
     */
    void setMaxSpeed(double max_speed_mps);

    /**
     * @brief 使用 ROS 参数中提供的航点生成轨迹。
     *
     * 该方法会从节点内部读取 `waypoints` 和 `stop_index` 参数，
     * 然后转交给 `planTrajectoryWithWaypoints` 处理。
     *
     * @param trajectory 输出轨迹对象指针。
     * @return true 表示生成了有效轨迹，否则返回 false。
     */
    bool planTrajectory(mav_trajectory_generation::Trajectory* trajectory);

    /**
     * @brief 使用显式给定的航点列表生成轨迹。
     *
     * @param waypoint_flat_list 扁平化航点列表，格式为 [x1, y1, z1, x2, y2, z2, ...]，单位为米。
     * @param stop_waypoint_index 需要完全停下来的航点索引（-1 表示禁用该约束）。
     * @param trajectory 需要填充的输出轨迹对象。
     * @return true 表示规划成功且轨迹有效。
     */
    bool planTrajectoryWithWaypoints(const std::vector<double>& waypoint_flat_list, int stop_waypoint_index,
                                     mav_trajectory_generation::Trajectory* trajectory);

    /**
     * @brief 另一套规划接口，可显式指定初始状态和约束。
     *
     * @param start_pos 初始位置向量，单位为米。
     * @param start_vel 初始速度向量，单位为米每秒。
     * @param v_max 最大允许速度（m/s）。
     * @param a_max 最大允许加速度（m/s^2）。
     * @param trajectory 输出轨迹对象。
     * @return true 表示规划成功。
     * @note 当前只是一个薄封装，内部仍会转到基于参数的规划逻辑。
     */
    bool planTrajectory(const Eigen::VectorXd& start_pos, const Eigen::VectorXd& start_vel, double v_max,
                        double a_max, mav_trajectory_generation::Trajectory* trajectory);

    /**
     * @brief 将已生成的轨迹发布到 RVIZ 标记和 `trajectory` 话题。
     *
     * @param trajectory 需要发布的轨迹。
     * @return true 表示发布成功。
     */
    bool publishTrajectory(const mav_trajectory_generation::Trajectory& trajectory);

    /**
     * @brief 将轨迹绘制成一组可视化标记。
     *
     * @param trajectory 需要采样并绘制的轨迹。
     * @param marker_spacing_m 姿态标记之间的间距，单位为米。
     * @param frame_id 标记所处的 TF 坐标系。
     * @param marker_array 需要填充的输出标记数组。
     */
    void drawMavTrajectory(const mav_trajectory_generation::Trajectory& trajectory, double marker_spacing_m,
                           const std::string& frame_id, visualization_msgs::msg::MarkerArray* marker_array);

   private:
    rclcpp::Node::SharedPtr node_;

    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr pub_markers_;
    rclcpp::Publisher<mav_planning_msgs::msg::PolynomialTrajectory4D>::SharedPtr pub_trajectory_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_odom_;

    Eigen::Affine3d current_pose_;
    Eigen::Vector3d current_velocity_;
    Eigen::Vector3d current_angular_velocity_;
    bool has_current_pose_{false};

    double max_speed_mps_;             // 米每秒
    double max_accel_mps2_;            // 米每二次方秒
    double max_angular_speed_radps_;   // 弧度每秒
    double max_angular_accel_radps2_;  // 弧度每二次方秒
};

#endif  // BASIC_WAYPOINT_PKG__PLANNER_HPP_
