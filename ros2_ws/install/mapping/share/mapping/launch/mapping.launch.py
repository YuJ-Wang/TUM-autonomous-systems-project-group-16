#!/usr/bin/env python3

from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    config = PathJoinSubstitution([FindPackageShare("mapping"), "config", "mapping.yaml"])

    voxel = Node(
        package="mapping",
        executable="voxel_grid_mapper_node",
        name="voxel_grid_mapper_node",
        output="screen",
        parameters=[config],
        remappings=[
            ("odometry", "/current_state_est"),
            ("pointcloud", "/perception/pointcloud"),
            ("global_map_raw", "/global_map_raw"),
            ("frontier_goal", "/frontier_goal"),
        ],
    )

    pub = Node(
        package="mapping",
        executable="global_map_publisher_node",
        name="global_map_publisher_node",
        output="screen",
        remappings=[
            ("global_map_raw", "/global_map_raw"),
            ("global_map", "/global_map"),
        ],
    )

    return LaunchDescription([voxel, pub])
