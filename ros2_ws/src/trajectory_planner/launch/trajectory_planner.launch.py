#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')

    config_file = PathJoinSubstitution([
        FindPackageShare('trajectory_planner'), 'config', 'trajectory_planner.yaml'
    ])

    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='false'),

        Node(
            package='trajectory_planner',
            executable='trajectory_planner_node',
            name='trajectory_planner_node',
            output='screen',
            parameters=[
                config_file,
                {'use_sim_time': use_sim_time},
            ],
            # Topic wiring:
            #   path                (Path)                         <- path_planner
            #   command/trajectory  (MultiDOFJointTrajectory)      -> controller
            #   trajectory_status   (String)                       -> status output
        ),
    ])
