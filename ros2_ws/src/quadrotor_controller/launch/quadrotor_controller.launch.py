#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")
    config_file = PathJoinSubstitution(
        [FindPackageShare("quadrotor_controller"), "config", "controller.yaml"]
    )

    return LaunchDescription([
        DeclareLaunchArgument("use_sim_time", default_value="true"),
        Node(
            package="quadrotor_controller",
            executable="controller_interface_node",
            name="controller_interface_node",
            output="screen",
            parameters=[config_file, {"use_sim_time": use_sim_time}],
        ),
    ])
