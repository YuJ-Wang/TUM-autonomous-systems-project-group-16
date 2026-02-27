# AutonomousSystems2025

## SubTerrain Challenge (Project)

![Schematics of the Drone](DroneforCave.png)

## Prerequisites

### System Requirements
- Ubuntu 24.04
- ROS2 Jazzy
- OpenCV
- Eigen3

### Quick Installation (Recommended)
```bash
cd <YOUR_WORKSPACE>
chmod +x install_dependencies.sh
./install_dependencies.sh
```

### Manual Installation
```bash
# Install ROS2 Jazzy dependencies
sudo apt update
sudo apt install -y \
    ros-jazzy-cv-bridge \
    ros-jazzy-vision-opencv \
    ros-jazzy-octomap \
    ros-jazzy-octomap-msgs \
    ros-jazzy-octomap-ros \
    ros-jazzy-tf2-ros \
    ros-jazzy-tf2-geometry-msgs \
    ros-jazzy-visualization-msgs

# Install Eigen3
sudo apt install -y libeigen3-dev
```

## How to Run

### Build the workspace
```bash
cd <YOUR_WORKSPACE>/ros2_ws
colcon build
source install/setup.bash
```

### Quick Start (All nodes in separate terminals)
```bash
cd <YOUR_WORKSPACE>
chmod +x quick_start.sh
./quick_start.sh
```

**Note:** If you encounter terminal launch errors due to snap conflicts, use the manual start method below.

### Manual Start (Recommended - Step by step)

### Launch the simulation
**Terminal 1: Unity Simulation**
```bash
cd <YOUR_WORKSPACE>/ros2_ws
source install/setup.bash
ros2 launch simulation simulation.launch.py
```

### Launch the perception node
**Terminal 2: Depth to Point Cloud Converter**
```bash
cd <YOUR_WORKSPACE>/ros2_ws
source install/setup.bash
ros2 launch perception_pkg perception.launch.py
```

### Launch the OctoMap 3D mapping node
**Terminal 3: OctoMap Generator**
```bash
cd <YOUR_WORKSPACE>/ros2_ws
source install/setup.bash
ros2 launch perception_pkg octomap.launch.py
```

### Launch RViz2 for visualization
**Terminal 4: RViz2**
```bash
cd <YOUR_WORKSPACE>
./start_rviz2.sh
```

**Note:** Replace `<YOUR_WORKSPACE>` with your actual workspace path (e.g., `~/autonomoussystems2025`)

### Visualization in RViz2

**Step 1: Set Fixed Frame**
- In RViz2, set **Fixed Frame** to `world` in the Global Options panel

**Why use `world` frame?**
- `world`: Static global reference frame - the map stays fixed while the drone moves
- `true_body`: Moves and rotates with the drone - would make the map appear to move
- Using `world` allows you to see:
  - The drone's trajectory through space
  - The accumulated 3D map in a stable reference frame
  - Spatial relationships between objects clearly

**Step 2: Add Point Cloud Display**
1. Click "Add" → "By topic" → `/camera/depth/points` → "PointCloud2"
2. Select the PointCloud2 display
3. Change **Color Transformer** to "AxisColor"
4. Set **Axis** to "Z" for height-based coloring

**Step 3: Add OctoMap Display**
1. Click "Add" → "By topic" → `/octomap_markers` → "MarkerArray"
2. The 3D voxel map will appear with color-coded height information:
   - Red voxels = Higher altitude
   - Green voxels = Lower altitude
   - Each voxel represents a 15cm³ occupied space

**Tip:** If you don't see the markers immediately, wait a few seconds for the map to build up as the drone explores.

### Verify System is Running

Check that all nodes are active:
```bash
# List running nodes
ros2 node list

# You should see:
# /depth_to_pointcloud
# /pointcloud_to_octomap
# /unity_ros
# /rviz2 (if RViz2 is running)

# Check topic rates
ros2 topic hz /camera/depth/points        # Should be ~5 Hz
ros2 topic hz /octomap_markers            # Should be ~1 Hz

# Monitor point cloud data
ros2 topic echo /camera/depth/points --once
```

## Project Structure

### Current Components:
- **Simulation** (`simulation`): Unity bridge, depth camera, semantic camera, IMU, state estimation
- **Perception** (`perception_pkg`):
  - `depth_to_pointcloud`: Converts 16-bit depth images to 3D point clouds (C++ implementation)
  - `pointcloud_to_octomap`: Builds incremental 3D occupancy map (OctoMap) from accumulated point clouds
  - `lantern_detector`: Detects lanterns using semantic + depth camera fusion for accurate 3D positioning
- **Controller** (`controller_pkg`): PID controller for drone flight control

### Key Features:
- **Real-time 3D Mapping**: Incremental OctoMap generation with 15cm voxel resolution
- **Optimized for VMware**: 8x downsampling for stable performance in virtualized environments
- **TF2 Integration**: Automatic coordinate transformation from camera frame to world frame
- **Dual Output**: Publishes both OctoMap binary format and MarkerArray for RViz2 visualization

### Lantern Detection

**How to run:**
```bash
cd <YOUR_WORKSPACE>/ros2_ws
source install/setup.bash
ros2 run perception_pkg lantern_detector
```

**View in RViz2:**
- Add → By topic → `/lantern_markers` → MarkerArray
- Yellow spheres (0.6m diameter) show detected lanterns in `world` frame
- Markers persist for 5 seconds even when temporarily out of view
- Lanterns stay fixed in world coordinates when drone moves

**Troubleshooting:**
- **Can't see lanterns**: Check Fixed Frame is `world` (not `true_body`)
- **Markers blinking**: Already fixed - markers have 5s lifetime for smooth visualization
- **No detections**: Verify both semantic and depth cameras are publishing:
  ```bash
  ros2 topic hz /Quadrotor/Sensors/SemanticCamera/image_raw
  ros2 topic hz /realsense/depth/image
  ```

**How it works:**
- Synchronizes semantic + depth camera images using `message_filters`
- Detects yellow pixels in semantic camera (lantern color)
- Backprojects pixels to 3D using depth data and camera intrinsics
- Transforms from camera frame → `world` frame using TF2
- Auto-merges duplicate detections within 1.5m threshold
- Weighted averaging for stable position estimates (smoother over time)

### To Be Implemented:
- **Path Planning**: A* or RRT* for collision-free navigation using OctoMap
- **Trajectory Generation**: Smooth trajectory planning with velocity/acceleration constraints
- **State Machine**: Mission coordination and autonomous exploration task management

## Troubleshooting

### RViz2 Crashes or Fails to Start
If you encounter library conflicts (especially with snap packages), use the provided launcher script:
```bash
cd <YOUR_WORKSPACE>
./start_rviz2.sh
```

### Point Cloud Shows 0 Points
- Check that Unity simulation is running
- Verify depth camera topic: `ros2 topic echo /realsense/depth/image --once`
- Ensure perception node is running: `ros2 node list | grep depth`

### OctoMap Not Visible in RViz2
- Use `/octomap_markers` topic with **MarkerArray** display type (not OccupancyGrid)
- Wait 5-10 seconds for initial map generation
- Check that Fixed Frame is set to `world`
- Verify octomap node is publishing: `ros2 topic hz /octomap_markers`

### Transform Errors
If you see "Could not transform" warnings:
- These are timing warnings and can be safely ignored
- The system uses TF2 buffer with 0.1s timeout for robustness
- Map building continues despite occasional transform misses

## Technical Notes

### Performance Tuning
- **Downsample Factor**: Set to 8 for VMware (reduces points by 64x)
- **OctoMap Resolution**: 0.15m voxels balance detail vs. memory
- **Publish Rate**: 1 Hz for map updates to reduce CPU load

### Coordinate Frames
- `world`: **Global reference frame** (static, never moves)
  - Used for: Map visualization, trajectory planning, global localization
  - OctoMap and markers are published in this frame
  - Best for RViz2 Fixed Frame to see the big picture
  
- `true_body`: **Drone body frame** (moves and rotates with the drone)
  - Origin at drone center of mass
  - X-axis points forward, Z-axis points up
  - Used for: Local control, sensor mounting offsets
  
- `Quadrotor/Sensors/DepthCamera`: **Camera optical frame**
  - Origin at camera lens
  - Mounted 0.3m forward of drone center (X-axis offset)
  - Depth images and point clouds originate here before transformation to world frame
