#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    """Launch PointCloud to OctoMap converter"""
    
    pointcloud_to_octomap_node = Node(
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
    )
    
    return LaunchDescription([
        pointcloud_to_octomap_node,
    ])
