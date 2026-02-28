from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Lantern Detector node
        Node(
            package='perception_pkg',
            executable='lantern_detector',
            name='lantern_detector',
            output='screen',
            parameters=[{
                'semantic_image_topic': '/Quadrotor/Sensors/SemanticCamera/image_raw',
                'camera_info_topic': '/Quadrotor/Sensors/SemanticCamera/camera_info',
                'output_topic': '/detected_lanterns',
                'min_area': 100,  # Minimum pixel area
                'max_lanterns': 4,  # Expected number of lanterns in cave
                'detection_distance': 10.0  # Maximum detection distance (meters)
            }]
        ),
    ])
