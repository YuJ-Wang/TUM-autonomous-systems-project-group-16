#!/usr/bin/env python3

from pathlib import Path

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def _default_simulator_binary():
    this_file = Path(__file__).resolve()
    candidates = []

    if len(this_file.parents) > 4:
        repo_root = this_file.parents[4]
        candidates.extend([
            repo_root / "Simulation" / "Simulation.x86_64",
            repo_root / "Simulation_HQ" / "Simulation_HQ.x86_64",
            repo_root / "Simulation_LQ" / "Simulation_LQ.x86_64",
        ])

    if len(this_file.parents) > 5:
        repo_root = this_file.parents[5]
        candidates.extend([
            repo_root / "Simulation" / "Simulation.x86_64",
            repo_root / "Simulation_HQ" / "Simulation_HQ.x86_64",
            repo_root / "Simulation_LQ" / "Simulation_LQ.x86_64",
        ])

    for candidate in candidates:
        if candidate.exists():
            return str(candidate)

    return "Simulation.x86_64"


def generate_launch_description():
    start_simulator = LaunchConfiguration("start_simulator")
    simulator_binary = LaunchConfiguration("simulator_binary")
    enable_perception = LaunchConfiguration("enable_perception")

    declared_args = [
        DeclareLaunchArgument("start_simulator", default_value="true"),
        DeclareLaunchArgument("simulator_binary", default_value=_default_simulator_binary()),
        DeclareLaunchArgument("enable_perception", default_value="true"),
    ]

    simulation_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("simulation"), "launch", "simulation.launch.py"])
        ),
        launch_arguments={
            "start_simulator": start_simulator,
            "simulator_binary": simulator_binary,
        }.items(),
    )

    perception_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("perception"), "launch", "perception.launch.py"])
        ),
        condition=IfCondition(enable_perception),
    )

    return LaunchDescription(declared_args + [simulation_launch, perception_launch])
