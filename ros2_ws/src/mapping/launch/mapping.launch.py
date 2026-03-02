#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")
    config_file = PathJoinSubstitution([FindPackageShare("mapping"), "config", "mapping.yaml"])

    mapper = Node(
        package="mapping",
        executable="voxel_grid_mapper_node",
        name="voxel_grid_mapper_node",
        output="screen",
        parameters=[config_file, {"use_sim_time": use_sim_time}],
        remappings=[
            # Use the proven perception package output (published by mission.launch.py's
            # perception.launch.py → depth_to_pointcloud with max_depth=100m, RELIABLE QoS)
            ("/mapping/pointcloud_in", "/camera/depth/points"),
        ],
    )

    map_publisher = Node(
        package="mapping",
        executable="global_map_publisher_node",
        name="global_map_publisher_node",
        output="screen",
        parameters=[config_file, {"use_sim_time": use_sim_time}],
    )

    return LaunchDescription([
        DeclareLaunchArgument("use_sim_time", default_value="true"),
        mapper,
        map_publisher,
    ])
