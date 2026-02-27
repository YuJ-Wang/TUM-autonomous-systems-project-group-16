#!/bin/bash
# RViz2 launcher script - avoid snap library conflicts

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR"
source ros2_ws/install/setup.bash
unset GTK_PATH
unset LD_LIBRARY_PATH
source /opt/ros/jazzy/setup.bash
/opt/ros/jazzy/bin/rviz2 "$@"
