# AutonomousSystems2025

## SubTerrain Challenge (Project)

![Schematics of the Drone](DroneforCave.png)

## Prerequisites

- Ubuntu 24.04
- ROS2 Jazzy
- OpenCV, Eigen3

### Installation
```bash
cd ~/autonomoussystems2025
chmod +x install_dependencies.sh
./install_dependencies.sh
```

## Build

```bash
cd ~/autonomoussystems2025/ros2_ws
colcon build
source install/setup.bash
```

## How to Run

Open separate terminals and run each command:

**Terminal 1: Simulation**
```bash
cd ~/autonomoussystems2025/ros2_ws
source install/setup.bash
ros2 launch simulation simulation.launch.py
```

**Terminal 2: Perception (depth + octomap)**
```bash
cd ~/autonomoussystems2025/ros2_ws
source install/setup.bash
ros2 launch perception perception.launch.py
```

**Terminal 3: Lantern Detection**
```bash
cd ~/autonomoussystems2025/ros2_ws
source install/setup.bash
ros2 launch detection lantern_detector.launch.py
```

**Terminal 4: RViz2**
```bash
cd ~/autonomoussystems2025
./start_rviz2.sh
```

## RViz2 Setup

1. Set **Fixed Frame** to `world`
2. Add displays:
   - `/camera/depth/points` → PointCloud2 (set Color Transformer to "AxisColor", Axis to "Z")
   - `/octomap_markers` → MarkerArray
   - `/detected_lanterns` → MarkerArray
   - `/lantern_debug_image` → Image (optional)

## Verify System

```bash
# Check running nodes
ros2 node list

# Check topics
ros2 topic hz /camera/depth/points
ros2 topic hz /octomap_markers
ros2 topic hz /detected_lanterns
```

## Troubleshooting

**No point cloud in RViz2:**
- Check simulation is running: `ros2 topic list | grep depth`
- Check perception is running: `ros2 node list | grep depth`

**RViz2 crashes:**
```bash
cd ~/autonomoussystems2025
./start_rviz2.sh
```
