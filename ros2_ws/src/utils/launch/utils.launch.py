#!/usr/bin/env python3
"""
Utils launch file — master launch that brings up the full simulation stack.

Includes:
  1. simulation.launch.py   – Unity sim, unity_ros, w_to_unity, state corruptor,
                               controller_node, static TFs
  2. perception.launch.py   – depth_to_pointcloud, pointcloud_to_octomap
  3. detection               – lantern_detector
  4. path_planner.launch.py – path_planner_node
  5. trajectory_planner.launch.py – trajectory_planner_node
  6. controller.launch.py   – controller_node (standalone, if not in simulation)
  7. mapping.launch.py      – (placeholder, TODO nodes)
  8. state_machine.launch.py – (placeholder, TODO nodes)
  9. perception_pipeline     – (placeholder, TODO nodes)
  10. quadrotor_controller   – (placeholder, TODO nodes)
  11. utils_node             – core utility node
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')

    declared_args = [
        DeclareLaunchArgument(
            'use_sim_time', default_value='false',
            description='Use simulation clock'),
    ]

    # ── 1. Simulation (Unity GUI + unity_ros + w_to_unity + TFs + corruptor) ──
    simulation_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('simulation'), 'launch', 'simulation.launch.py'])
        ),
    )

    # ── 2. Perception (depth→pointcloud, pointcloud→octomap) ──
    perception_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('perception'), 'launch', 'perception.launch.py'])
        ),
    )

    # ── 3. Detection (lantern detector) ──
    detection_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('detection'), 'launch', 'lantern_detector.launch.py'])
        ),
    )

    # ── 4. Path Planner ──
    path_planner_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('path_planner'), 'launch', 'path_planner.launch.py'])
        ),
        launch_arguments={'use_sim_time': use_sim_time}.items(),
    )

    # ── 5. Trajectory Planner ──
    trajectory_planner_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('trajectory_planner'), 'launch', 'trajectory_planner.launch.py'])
        ),
        launch_arguments={'use_sim_time': use_sim_time}.items(),
    )

    # ── 6. Mapping (placeholder — nodes TBD) ──
    mapping_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('mapping'), 'launch', 'mapping.launch.py'])
        ),
    )

    # ── 7. State Machine (placeholder — nodes TBD) ──
    state_machine_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('state_machine'), 'launch', 'state_machine.launch.py'])
        ),
    )

    # ── 8. Perception Pipeline (placeholder — nodes TBD) ──
    perception_pipeline_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('perception_pipeline'), 'launch', 'perception_pipeline.launch.py'])
        ),
    )

    # ── 9. Quadrotor Controller (placeholder — nodes TBD) ──
    quadrotor_controller_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('quadrotor_controller'), 'launch', 'quadrotor_controller.launch.py'])
        ),
    )

    # ── 10. Utils node ──
    utils_node = Node(
        package='utils',
        executable='utils_node',
        name='utils_node',
        output='screen',
        parameters=[{'use_sim_time': use_sim_time}],
    )

    return LaunchDescription(
        declared_args
        + [
            simulation_launch,
            perception_launch,
            detection_launch,
            path_planner_launch,
            trajectory_planner_launch,
            mapping_launch,
            state_machine_launch,
            perception_pipeline_launch,
            quadrotor_controller_launch,
            utils_node,
        ]
    )
