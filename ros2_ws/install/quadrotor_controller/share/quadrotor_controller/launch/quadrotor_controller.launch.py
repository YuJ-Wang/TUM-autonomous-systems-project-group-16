#!/usr/bin/env python3

from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    config = PathJoinSubstitution([FindPackageShare("quadrotor_controller"), "config", "controller.yaml"])

    node = Node(
        package="quadrotor_controller",
        executable="controller_interface_node",
        name="controller_interface_node",
        output="screen",
        parameters=[config],
        remappings=[
            ("trajectory_input", "/planning/trajectory"),
            ("odometry", "/current_state_est"),
            ("desired_state", "/desired_state"),
            ("status", "/planning/controller_interface_status"),
        ],
    )

    return LaunchDescription([node])
