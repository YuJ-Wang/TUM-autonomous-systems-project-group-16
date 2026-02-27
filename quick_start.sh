#!/bin/bash
# Quick start script for SubTerrain Challenge
# Launches all required nodes in separate terminals

WORKSPACE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROS2_WS="${WORKSPACE_DIR}/ros2_ws"

echo "=================================================="
echo "Starting SubTerrain Challenge System"
echo "=================================================="

# Check if workspace is built
if [ ! -d "${ROS2_WS}/install" ]; then
    echo "ERROR: Workspace not built!"
    echo "Please run: cd ros2_ws && colcon build"
    exit 1
fi

echo ""
echo "This script will launch multiple terminals:"
echo "  1. Unity Simulation"
echo "  2. Perception (Depth to PointCloud)"
echo "  3. OctoMap 3D Mapping"
echo "  4. RViz2 Visualization"
echo ""
echo "Press Enter to continue or Ctrl+C to cancel..."
read

# Function to launch terminal with clean environment
launch_terminal() {
    local title="$1"
    local command="$2"
    
    # Unset problematic environment variables to avoid snap conflicts
    env -u GTK_PATH -u LD_LIBRARY_PATH gnome-terminal --title="$title" -- bash -c "$command; exec bash"
}

# Launch simulation
echo "Launching Unity Simulation..."
launch_terminal "1. Unity Simulation" "
cd ${ROS2_WS}
source install/setup.bash
ros2 launch simulation simulation.launch.py
"

sleep 3

# Launch perception
echo "Launching Perception Node..."
launch_terminal "2. Perception" "
cd ${ROS2_WS}
source install/setup.bash
ros2 launch perception_pkg perception.launch.py
"

sleep 2

# Launch octomap
echo "Launching OctoMap Node..."
launch_terminal "3. OctoMap" "
cd ${ROS2_WS}
source install/setup.bash
ros2 launch perception_pkg octomap.launch.py
"

sleep 2

# Launch RViz2
echo "Launching RViz2..."
launch_terminal "4. RViz2" "
cd ${WORKSPACE_DIR}
./start_rviz2.sh
"

echo ""
echo "=================================================="
echo "✅ All nodes launched!"
echo "=================================================="
echo ""
echo "Configure RViz2:"
echo "  1. Set Fixed Frame to 'world'"
echo "  2. Add /camera/depth/points (PointCloud2)"
echo "  3. Add /octomap_markers (MarkerArray)"
echo ""
echo "To stop all nodes, close the terminal windows"
echo "=================================================="
