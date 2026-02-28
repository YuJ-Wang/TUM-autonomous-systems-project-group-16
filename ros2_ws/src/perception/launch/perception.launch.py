#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='perception',
            executable='depth_to_pointcloud',
            name='depth_to_pointcloud',
            output='screen',
            parameters=[{
                'depth_topic': '/realsense/depth/image',
                'camera_info_topic': '/realsense/depth/camera_info',
                'output_topic': '/camera/depth/points',
                'max_depth': 100.0,
                'downsample_factor': 1,
            }]
        ),
        Node(
            package='perception',
            executable='pointcloud_to_octomap',
            name='pointcloud_to_octomap',
            output='screen',
            parameters=[{
                'pointcloud_topic': '/camera/depth/points',
                'output_topic': '/octomap',
                'resolution': 0.15,
                'max_range': 100.0,
                'publish_rate': 1.0,
                'frame_id': 'world'
            }]
        ),
    ])
