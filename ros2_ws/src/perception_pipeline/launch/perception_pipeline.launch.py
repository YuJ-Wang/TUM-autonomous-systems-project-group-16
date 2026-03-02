#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")
    config_file = PathJoinSubstitution(
        [FindPackageShare("perception_pipeline"), "config", "perception_pipeline.yaml"]
    )

    semantic_sub = Node(
        package="perception_pipeline",
        executable="semantic_camera_subscriber_node",
        name="semantic_camera_subscriber_node",
        output="screen",
        parameters=[config_file, {"use_sim_time": use_sim_time}],
    )

    depth_to_cloud = Node(
        package="perception_pipeline",
        executable="depth_to_pointcloud_node",
        name="depth_to_pointcloud_node",
        output="screen",
        parameters=[config_file, {"use_sim_time": use_sim_time}],
    )

    object_detection = Node(
        package="perception_pipeline",
        executable="object_detection_node",
        name="object_detection_node",
        output="screen",
        parameters=[config_file, {"use_sim_time": use_sim_time}],
        remappings=[
            # The Unity semantic camera publishes here; remap to what the node expects
            ("/realsense/semantic/image_raw", "/Quadrotor/Sensors/SemanticCamera/image_raw"),
        ],
    )

    return LaunchDescription([
        DeclareLaunchArgument("use_sim_time", default_value="true"),
        semantic_sub,
        depth_to_cloud,
        object_detection,
    ])
