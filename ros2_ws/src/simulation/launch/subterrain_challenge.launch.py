#!/usr/bin/env python3

from pathlib import Path

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, SetEnvironmentVariable, TimerAction
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
    # Existing simulation/mission controls.
    start_simulator = LaunchConfiguration("start_simulator")
    simulator_binary = LaunchConfiguration("simulator_binary")
    enable_perception = LaunchConfiguration("enable_perception")

    # New scaffold package controls.
    use_sim_time = LaunchConfiguration("use_sim_time")
    planner_method = LaunchConfiguration("planner_method")
    enable_mapping = LaunchConfiguration("enable_mapping")
    enable_path_planner = LaunchConfiguration("enable_path_planner")
    enable_trajectory_planner = LaunchConfiguration("enable_trajectory_planner")
    enable_perception_pipeline = LaunchConfiguration("enable_perception_pipeline")
    enable_quadrotor_interface = LaunchConfiguration("enable_quadrotor_interface")
    enable_state_machine = LaunchConfiguration("enable_state_machine")
    enable_utils = LaunchConfiguration("enable_utils")

    declared_args = [
        DeclareLaunchArgument("start_simulator", default_value="true"),
        DeclareLaunchArgument("simulator_binary", default_value=_default_simulator_binary()),
        DeclareLaunchArgument("enable_perception", default_value="true"),
        DeclareLaunchArgument("use_sim_time", default_value="false"),
        DeclareLaunchArgument("planner_method", default_value="rrt_star"),
        DeclareLaunchArgument("enable_mapping", default_value="true"),
        DeclareLaunchArgument("enable_path_planner", default_value="true"),
        DeclareLaunchArgument("enable_trajectory_planner", default_value="true"),
        DeclareLaunchArgument("enable_perception_pipeline", default_value="true"),
        DeclareLaunchArgument("enable_quadrotor_interface", default_value="true"),
        DeclareLaunchArgument("enable_state_machine", default_value="true"),
        DeclareLaunchArgument("enable_utils", default_value="true"),
    ]

    # Base stack from the existing simulation package.
    mission_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("simulation"), "launch", "mission.launch.py"])
        ),
        launch_arguments={
            "start_simulator": start_simulator,
            "simulator_binary": simulator_binary,
            "enable_perception": enable_perception,
        }.items(),
    )

    # Additional scaffold packages layered on top.
    mapping_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("mapping"), "launch", "mapping.launch.py"])
        ),
        condition=IfCondition(enable_mapping),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    path_planner_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("path_planner"), "launch", "path_planner.launch.py"])
        ),
        condition=IfCondition(enable_path_planner),
        launch_arguments={
            "use_sim_time": use_sim_time,
            "planner_method": planner_method,
        }.items(),
    )

    trajectory_planner_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("trajectory_planner"), "launch", "trajectory_planner.launch.py"])
        ),
        condition=IfCondition(enable_trajectory_planner),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    perception_pipeline_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("perception_pipeline"), "launch", "perception_pipeline.launch.py"])
        ),
        condition=IfCondition(enable_perception_pipeline),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    quadrotor_interface_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution(
                [FindPackageShare("quadrotor_controller"), "launch", "quadrotor_controller.launch.py"]
            )
        ),
        condition=IfCondition(enable_quadrotor_interface),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    state_machine_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("state_machine"), "launch", "state_machine.launch.py"])
        ),
        condition=IfCondition(enable_state_machine),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    utils_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("utils"), "launch", "utils.launch.py"])
        ),
        condition=IfCondition(enable_utils),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    return LaunchDescription(
        declared_args
        + [
            # Ensure system libstdc++ is used so Anaconda's older version does not
            # shadow the GLIBCXX_3.4.32 symbol required by ROS 2 Jazzy libraries.
            SetEnvironmentVariable(
                "LD_PRELOAD", "/usr/lib/x86_64-linux-gnu/libstdc++.so.6"
            ),
            mission_launch,
            TimerAction(period=1.0, actions=[mapping_launch]),
            TimerAction(period=2.0, actions=[path_planner_launch]),
            TimerAction(period=3.0, actions=[trajectory_planner_launch]),
            TimerAction(period=3.5, actions=[quadrotor_interface_launch]),
            TimerAction(period=4.0, actions=[perception_pipeline_launch]),
            TimerAction(period=5.0, actions=[state_machine_launch]),
            utils_launch,
        ]
    )
