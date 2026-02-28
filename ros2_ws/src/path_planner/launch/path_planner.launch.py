#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')
    planner_method = LaunchConfiguration('planner_method')

    config_file = PathJoinSubstitution([
        FindPackageShare('path_planner'), 'config', 'path_planner.yaml'
    ])

    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        DeclareLaunchArgument('planner_method', default_value='astar'),

        Node(
            package='path_planner',
            executable='path_planner_node',
            name='path_planner_node',
            output='screen',
            parameters=[
                config_file,
                {
                    'use_sim_time': use_sim_time,
                    'planner_method': planner_method,
                },
            ],
            # Topic wiring:
            #   /current_state_est  (Odometry)        -> odometry input
            #   goal_pose           (PoseStamped)      <- state_machine
            #   frontier_goal       (Point)            <- mapping
            #   global_map          (GlobalMap)        <- mapping
            #   path                (Path)             -> trajectory_planner
            #   planner_status      (String)           -> status output
        ),
    ])
