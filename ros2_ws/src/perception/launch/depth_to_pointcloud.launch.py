#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    """Launch depth to point cloud converter"""
    
    depth_to_pointcloud_node = Node(
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
    )
    
    return LaunchDescription([
        depth_to_pointcloud_node,
    ])
