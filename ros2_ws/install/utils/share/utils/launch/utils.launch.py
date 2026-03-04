#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()

    # core utility node
    ld.add_action(Node(
        package='utils', executable='utils_node', name='utils_node', output='screen'))

    # mapping nodes
    ld.add_action(Node(
        package='mapping', executable='voxel_grid_mapper_node', name='voxel_grid_mapper_node', output='screen'))
    ld.add_action(Node(
        package='mapping', executable='global_map_publisher_node', name='global_map_publisher_node', output='screen'))

    # path planning
    ld.add_action(Node(
        package='path_planner', executable='path_planner_node', name='path_planner_node', output='screen'))

    # trajectory planning
    ld.add_action(Node(
        package='trajectory_planner', executable='trajectory_planner_node', name='trajectory_planner_node', output='screen'))

    # perception nodes
    ld.add_action(Node(
        package='perception', executable='light_detection_node', name='light_detection_node', output='screen'))

    # perception pipeline
    ld.add_action(Node(
        package='perception_pipeline', executable='semantic_camera_subscriber_node', name='semantic_camera_subscriber_node', output='screen'))
    ld.add_action(Node(
        package='perception_pipeline', executable='depth_to_pointcloud_node', name='depth_to_pointcloud_node', output='screen'))
    ld.add_action(Node(
        package='perception_pipeline', executable='object_detection_node', name='object_detection_node', output='screen'))

    # simulation and bridge
    ld.add_action(Node(
        package='simulation', executable='w_to_unity', name='w_to_unity', output='screen'))
    ld.add_action(Node(
        package='simulation', executable='state_estimate_corruptor_node', name='state_estimate_corruptor_node', output='screen'))
    ld.add_action(Node(
        package='simulation', executable='unity_ros', name='unity_ros', output='screen'))

    # state machine
    ld.add_action(Node(
        package='state_machine', executable='mission_state_machine_node', name='mission_state_machine_node', output='screen'))

    # quadrotor controller
    ld.add_action(Node(
        package='quadrotor_controller', executable='controller_interface_node', name='controller_interface_node', output='screen'))

    # controller package
    ld.add_action(Node(
        package='controller_pkg', executable='controller_node', name='controller_node', output='screen'))

    return ld
