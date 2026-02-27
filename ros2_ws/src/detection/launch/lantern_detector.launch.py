#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    """Launch lantern detector"""
    
    lantern_detector_node = Node(
        package='detection',
        executable='lantern_detector',
        name='lantern_detector',
        output='screen',
        parameters=[{
            'semantic_topic': '/Quadrotor/Sensors/SemanticCamera/image_raw',
            'depth_topic': '/realsense/depth/image',
            'depth_info_topic': '/realsense/depth/camera_info',
            'world_frame': 'world',
            'distance_threshold': 1.5,
            'min_depth': 0.5,
            'max_depth': 30.0,
        }]
    )
    
    return LaunchDescription([
        lantern_detector_node,
    ])
