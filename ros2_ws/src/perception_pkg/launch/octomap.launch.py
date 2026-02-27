from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # PointCloud to OctoMap node
        Node(
            package='perception_pkg',
            executable='pointcloud_to_octomap',
            name='pointcloud_to_octomap',
            output='screen',
            parameters=[{
                'pointcloud_topic': '/camera/depth/points',
                'output_topic': '/octomap',
                'resolution': 0.15,  # 15cm voxel size for better performance in VMware
                'max_range': 100.0,
                'publish_rate': 1.0,  # Publish every 1 second
                'frame_id': 'world'
            }]
        ),
    ])
