#!/usr/bin/env python3

from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    config = PathJoinSubstitution([FindPackageShare("perception"), "config", "perception.yaml"])

    node = Node(
        package="perception",
        executable="light_detection_node",
        name="light_detection_node",
        output="screen",
        parameters=[config],
        remappings=[
            ("/realsense/semantic/image_raw", "/realsense/rgb/image_rect_raw_left"),
            ("/realsense/depth/image", "/realsense/depth/image_rect_raw"),
            ("/realsense/depth/camera_info", "/realsense/depth/camera_info"),
        ],
    )

    return LaunchDescription([node])
