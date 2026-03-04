#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")

    return LaunchDescription([
        DeclareLaunchArgument(
            "use_sim_time",
            default_value="false",
            description="Use /clock simulation time",
        ),
        Node(
            package="mav_trajectory_generation",
            executable="trajectory_sampler_node",
            name="sampler",
            output="screen",
            parameters=[{"use_sim_time": use_sim_time}],
        ),
    ])
