#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, EmitEvent, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.events import Shutdown
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")
    config_file = PathJoinSubstitution([FindPackageShare("state_machine"), "config", "state_machine.yaml"])

    mission_state_machine_node = Node(
        package="state_machine",
        executable="mission_state_machine_node",
        name="mission_state_machine_node",
        output="screen",
        parameters=[config_file, {"use_sim_time": use_sim_time}],
    )

    stop_launch_on_mission_exit = RegisterEventHandler(
        OnProcessExit(
            target_action=mission_state_machine_node,
            on_exit=[EmitEvent(event=Shutdown(reason="mission_state_machine_node exited"))],
        )
    )

    return LaunchDescription([
        DeclareLaunchArgument("use_sim_time", default_value="true"),
        mission_state_machine_node,
        stop_launch_on_mission_exit,
    ])
