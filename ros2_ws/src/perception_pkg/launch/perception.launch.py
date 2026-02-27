#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    """Launch perception pipeline"""
    
    # Get RViz config file path
    pkg_dir = get_package_share_directory('perception_pkg')
    rviz_config = os.path.join(pkg_dir, 'rviz', 'perception.rviz')
    
    # Depth image to point cloud conversion node
    depth_to_pointcloud_node = Node(
        package='perception_pkg',
        executable='depth_to_pointcloud',
        name='depth_to_pointcloud',
        output='screen',
        parameters=[{
            'depth_topic': '/realsense/depth/image',
            'camera_info_topic': '/realsense/depth/camera_info',
            'output_topic': '/camera/depth/points',
            'max_depth': 100.0,  # Maximum depth range (meters) - increased for far objects
            'downsample_factor': 1,  # No downsampling for maximum detail (1 = use every pixel)
        }]
    )
    
    # RViz2 visualization node
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config],
        output='screen'
    )
    
    return LaunchDescription([
        depth_to_pointcloud_node,
        # RViz2 needs to be started manually to avoid library conflicts
        # Usage: rviz2 -d ~/autonomoussystems2025/ros2_ws/install/perception_pkg/share/perception_pkg/rviz/perception.rviz
    ])
