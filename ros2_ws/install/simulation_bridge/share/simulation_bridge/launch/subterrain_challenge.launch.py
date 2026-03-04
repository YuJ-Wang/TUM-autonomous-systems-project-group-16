#!/usr/bin/env python3

from pathlib import Path

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def _clear_runtime_logs(_context):
    # 中文注释：每次启动总入口时只清空项目自己的日志文件。
    # 不能在 launch 运行中删除 ~/.ros/log，因为 launch 自己已经在使用当前轮次的 launch.log。
    cwd = Path.cwd()
    for log_name in ("lanterns_log.csv", "statemachine_events.log"):
        log_path = cwd / log_name
        try:
            if log_path.exists():
                log_path.unlink()
        except OSError:
            pass

    return []


def generate_launch_description():
    clear_logs = OpaqueFunction(function=_clear_runtime_logs)

    simulation = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare("simulation"), "launch", "simulation.launch.py"])
        )
    )
    return LaunchDescription([clear_logs, simulation])
