# TUM Autonomous Systems 2025 — Sub-Terrain Challenge

## 📌 Description and Task

This repository is built upon the course "Autonome Systeme" (LRG6300) taught at the Technical University of Munich (TUM), aiming to develop a fully autonomous drone system capable of exploring unknown underground cave environments. The system is built on a Unity virtual environment and implemented using **ROS 2 (Jazzy)**. The drone must locate four lanterns inside a cave, construct a 3D voxel map of the environment, and return home — all without any predefined waypoints during cave exploration.

![Schematics of the Drone](DroneforCave.png)

---

## ✈️ Members

- Yujia Wang
- Ziming Liu
- Jiacheng Li
- Nihat Akin
- Iliasu Olayiwola Salaudeen

---

## 🚦 Prerequisites and Running

- **Ubuntu 24.04**
- **ROS 2 Jazzy**

Clone the repository and enter the workspace:

```bash
git clone https://gitlab.lrz.de/00000000014C07CD/autosys13.git
cd autonomoussystems2025/ros2_ws
```

Install dependencies:

```bash
sudo apt install ros-jazzy-desktop python3-colcon-common-extensions
```

Build the workspace:

```bash
source /opt/ros/jazzy/setup.bash
colcon build --symlink-install
source install/setup.bash
```

Download the Unity simulation binary (`Simulation.x86_64`) and place it in the repo root under
`Simulation/`. The launch file auto-detects the binary from any of:

- `autonomoussystems2025/Simulation/Simulation.x86_64`
- `autonomoussystems2025/Simulation_HQ/Simulation_HQ.x86_64`
- `autonomoussystems2025/Simulation_LQ/Simulation_LQ.x86_64`

Then launch the full mission:

```bash
ros2 launch simulation subterrain_challenge.launch.py
```

If auto-detection fails, provide a path explicitly:

```bash
ros2 launch simulation subterrain_challenge.launch.py \
  simulator_binary:=/absolute/path/to/Simulation.x86_64
```

**Note:** The launch file automatically sets `LD_PRELOAD` to the system `libstdc++.so.6` to
resolve `GLIBCXX_3.4.32` compatibility issues. `use_sim_time` is `false` since the Unity
simulator does not publish a `/clock` topic. Each subsystem can be individually disabled:

```bash
# Run only the base simulation (no autonomous stack)
ros2 launch simulation subterrain_challenge.launch.py \
  enable_mapping:=false \
  enable_perception_pipeline:=false \
  enable_path_planner:=false \
  enable_trajectory_planner:=false \
  enable_quadrotor_interface:=false \
  enable_state_machine:=false \
  enable_utils:=false

# Disable Unity process, run only ROS nodes
ros2 launch simulation subterrain_challenge.launch.py start_simulator:=false

# Disable state-estimate corruption for first-flight debugging
ros2 launch simulation subterrain_challenge.launch.py corrupt_state_estimate:=false
```

---

## ✅ Task List

- ✅ Find and locate four lanterns in the cave environment.
- ✅ Generate a 3D voxel-grid representation of the cave.
- ✅ Develop a mission state machine for the drone.
- ✅ Build the perception pipeline for lantern detection.
- ✅ Implement a path planner and trajectory planner for autonomous navigation.
- ✅ Implement a 100 Hz trajectory sampler controller interface.
- ✅ Implement frontier-based autonomous exploration (no predefined cave waypoints).
- ✅ Full mission success (takeoff → cave entrance → explore → return → land).

---

## 🗺️ System Architecture

```
Unity Simulator
  ├─ /realsense/depth/image
  ├─ /realsense/semantic/image_raw
  └─ /current_state_est  (+ optional drift/jump corruption)
        │
        ├─→ [Perception Pipeline]  object_detection_node
        │       └─→ /perception/lantern_poses  →  State Machine
        │
        ├─→ [Perception (legacy)]  depth_to_pointcloud (perception pkg)
        │       └─→ /camera/depth/points  →  Mapper
        │
        ├─→ [Mapping]      voxel_grid_mapper_node
        │       └─→ /mapping/global_map  →  Path Planner + State Machine
        │
        └─→ [State Machine]  mission_state_machine_node
                └─→ /planning/goal  →  Path Planner
                        └─→ /planning/path  →  Trajectory Planner
                                └─→ /planning/trajectory  →  Controller Interface
                                        └─→ /command/trajectory  →  Controller (.so)
                                                └─→ rotor_speed_cmds  →  Unity Simulator
```

**Mission States:** `INIT → TAKEOFF → TO_CAVE_ENTRANCE → EXPLORE → RETURN_HOME → LAND → COMPLETE`

---

## 🍔 Modules

---

### 1️⃣ Perception

The perception module detects lanterns inside the cave and generates point clouds from the
drone's depth and semantic cameras.

**Approach: Semantic Colour Masking + 3D Backprojection**

The `object_detection_node` fuses a semantic segmentation image with depth data to detect
yellow lanterns in 3D space. A colour mask isolates yellow pixels (BGR: 4, 235, 255 ± 18
tolerance). Morphological operations (erode → dilate) remove noise and connect adjacent blobs.
Connected-component labelling selects the largest region above a minimum pixel threshold. Each
pixel in the region is back-projected to 3D world coordinates using the pinhole camera model
and the live depth image. The centroid of the resulting 3D cluster is recorded as a lantern
detection. A 3 m deduplication radius prevents double-counting the same lantern from multiple
viewpoints.

The system runs **two parallel depth-to-pointcloud pipelines**:

- **`perception` package** (`depth_to_pointcloud` node): publishes to `/camera/depth/points`
  using RELIABLE QoS and a 100 m max depth. This is the **active mapping source**.
- **`perception_pipeline` package** (`depth_to_pointcloud_node`): publishes to
  `/perception/pointcloud` using SensorDataQoS (BEST_EFFORT) and a 30 m max depth. Currently
  not used by the mapper.

**Dependencies:**
- OpenCV (morphological operations, connected components)
- TF2 (world-frame transforms)
- `utils` package (custom `LanternPoseArray` message)

**Key Nodes:**

| Node | Package |
|------|---------|
| `object_detection_node` | `perception_pipeline` |
| `depth_to_pointcloud_node` | `perception_pipeline` |
| `light_detection_node` | `perception` |

**Key Topics:**

| Topic | Type | Direction |
|-------|------|-----------|
| `/realsense/semantic/image_raw` | `sensor_msgs/Image` | Subscribed |
| `/realsense/depth/image` | `sensor_msgs/Image` | Subscribed |
| `/realsense/depth/camera_info` | `sensor_msgs/CameraInfo` | Subscribed |
| `/perception/lantern_poses` | `utils/LanternPoseArray` | Published (`perception_pipeline`) |
| `/camera/depth/points` | `sensor_msgs/PointCloud2` | Published (`perception` pkg → mapper) |
| `/detected_points` | `geometry_msgs/PointStamped` | Published (legacy) |

**Key Parameters:**
- `mask_b/g/r`: 4 / 235 / 255 (BGR yellow target)
- `tolerance`: 18 (per-channel colour tolerance)
- `min_component_pixels`: 30
- `dedup_radius_m`: 3.0 m
- `max_depth_m`: 35.0 m

---

### 2️⃣ Mapping

The mapping module builds a live 3D occupancy voxel grid from depth point clouds and identifies
unexplored frontiers to drive autonomous exploration.

**Approach: Ray-Cast Voxel Grid + Frontier Scoring**

The `voxel_grid_mapper_node` processes each incoming point cloud frame by ray-casting from the
camera origin through every sampled point (stride = 8 for efficiency). The point cloud is
sourced from the `perception` package's `depth_to_pointcloud` node via `/camera/depth/points`
(RELIABLE QoS, 100 m max depth). Voxels along each ray
are marked **free**; the terminal voxel at the measured depth is marked **occupied**. All
voxels are stored in a hash map keyed by a 64-bit packed integer (21 bits per axis), enabling
O(1) occupancy lookup. Every second, frontiers are identified as free voxels adjacent to
unexplored space within altitude bounds. Each frontier is scored as:

```
score = euclidean_distance + frontier_x_bias × max(0, frontier.x − drone.x)
```

The `x_progress` term biases the drone toward deeper cave regions; the distance term prefers
reachable frontiers. The best-scored frontier is published as `frontier_goal` in the
`GlobalMap` message consumed by the state machine.

**Dependencies:**
- TF2 (sensor → world frame)
- `utils` package (custom `GlobalMap` message)

**Key Nodes:**

| Node | Package |
|------|---------|
| `voxel_grid_mapper_node` | `mapping` |
| `global_map_publisher_node` | `mapping` |

**Key Topics:**

| Topic | Type | Direction |
|-------|------|-----------|
| `/mapping/pointcloud_in` | `sensor_msgs/PointCloud2` | Subscribed |
| `/current_state_est` | `nav_msgs/Odometry` | Subscribed |
| `/mapping/global_map_raw` | `utils/GlobalMap` | Published |
| `/mapping/global_map` | `utils/GlobalMap` | Published |

**Key Parameters:**
- `resolution`: 0.5 m (voxel side length)
- `point_stride`: 8 (process every 8th point for efficiency)
- `serialization_voxel_limit`: 150 000
- `frontier_x_bias`: 2.0 (forward exploration weight)
- `frontier_republish_distance_m`: 1.5 m

---

### 3️⃣ Navigation (Path Planner + Trajectory Planner)

The navigation module translates high-level goal positions into smooth, physically feasible
trajectories via two sequential nodes: a 3D A\* path planner and a trapezoidal trajectory
generator.

#### Path Planner — A\* in Voxel Space

The `path_planner_node` receives a goal from the state machine and a live occupancy map from
the mapper. It inflates all occupied voxels by a configurable safety radius (0.8 m) and runs
A\* on the resulting voxel graph with 26-connectivity (full 3D diagonals). The heuristic is
the Euclidean distance to the goal (admissible). If A\* exceeds 500 000 node expansions, a
straight-line fallback path is returned. The resulting voxel path is interpolated to a
fixed 30-point waypoint list and published on `/planning/path`.

#### Trajectory Planner — Trapezoidal Speed Profile

The `trajectory_generator_node` converts the 30-point waypoint list into a
`MultiDOFJointTrajectory` with velocities, accelerations, yaw, and timestamps:

1. **Forward pass** — accelerate from 0 toward `desired_speed` at `max_acceleration`.
2. **Backward pass** — ensure deceleration to 0 at the final waypoint.
3. **Timestamp generation** — `dt` per segment from average speed; floored at `min_segment_dt`.
4. **Derivatives** — velocities from `speed × unit_direction`; accelerations from finite differences.
5. **Yaw** — aligned with travel direction (`atan2(Δy, Δx)`).

**Dependencies:**
- `utils` package (`GlobalMap`, `SaveMap`)
- `nav_msgs`, `geometry_msgs`, `trajectory_msgs`

**Key Nodes:**

| Node | Package |
|------|---------|
| `path_planner_node` | `path_planner` |
| `trajectory_generator_node` | `trajectory_planner` |

**Key Topics:**

| Topic | Type | Direction |
|-------|------|-----------|
| `/planning/goal` | `geometry_msgs/PoseStamped` | Subscribed (path planner) |
| `/mapping/global_map` | `utils/GlobalMap` | Subscribed (path planner) |
| `/current_state_est` | `nav_msgs/Odometry` | Subscribed (path planner) |
| `/planning/path` | `nav_msgs/Path` | Published / Subscribed |
| `/planning/trajectory` | `trajectory_msgs/MultiDOFJointTrajectory` | Published |

**Key Parameters — Path Planner:**
- `safety_radius_m`: 0.8 m
- `astar_max_expansions`: 500 000
- `astar_search_margin_vox`: 15 (±15-voxel bounding box around direct line)
- `interpolation_points`: 30
- `min_flight_altitude`: 2.0 m

**Key Parameters — Trajectory Planner:**
- `desired_speed`: 2.0 m/s
- `max_acceleration`: 1.5 m/s²
- `min_segment_dt`: 0.05 s

---

### 4️⃣ Control

The control module bridges the planned trajectory to the precompiled low-level geometric
controller. It consists of a high-frequency trajectory sampler (`quadrotor_controller`) and
the precompiled controller library (`controller_pkg`).

**Approach: 100 Hz Trajectory Sampler + Precompiled Geometric Controller**

The `controller_interface_node` receives the 30-point planned trajectory from the trajectory
planner and streams single-point setpoints at **100 Hz** by linearly interpolating position,
velocity, acceleration, and yaw between consecutive trajectory points based on elapsed
wall-clock time. This decouples the planning rate (~0.5–1 Hz) from the control rate (100 Hz),
ensuring smooth reference tracking regardless of planning latency.

A **5 Hz watchdog** publishes a hover command at the current odometry position if no trajectory
has been received within 5 seconds of node startup, preventing the drone from falling during
initialisation or planning delays.

The streamed single-point `MultiDOFJointTrajectory` is consumed by the precompiled
**libcontroller_lib.so**, which implements a geometric PD controller computing desired thrusts
and torques mapped to individual rotor speed commands.

**Dependencies:**
- `mav_msgs` (rotor speed commands)
- `mav_planning_msgs` (trajectory message conversions)
- Precompiled `libcontroller_lib.so` (linked via `controller_pkg`)

**Key Nodes:**

| Node | Package |
|------|---------|
| `controller_interface_node` | `quadrotor_controller` |
| `controller_node` (in `.so`) | `controller_pkg` |

**Key Topics:**

| Topic | Type | Direction |
|-------|------|-----------|
| `/planning/trajectory` | `trajectory_msgs/MultiDOFJointTrajectory` | Subscribed |
| `/current_state_est` | `nav_msgs/Odometry` | Subscribed |
| `/command/trajectory` | `trajectory_msgs/MultiDOFJointTrajectory` | Published (to `.so`) |
| `rotor_speed_cmds` | `mav_msgs/Actuators` | Published (to simulator) |

**Key Parameters:**
- `trajectory_timeout_s`: 5.0 s (watchdog hover delay)
- Controller gains (`kx`, `kv`, `kr`, `komega`) loaded by precompiled `.so`

---

### 5️⃣ State Machine

The state machine module implements the high-level mission logic as a seven-state finite state
machine (FSM), orchestrating all other subsystems from takeoff through landing.

**States and Transitions:**

```
INIT
 └─→ TAKEOFF              (publish takeoff goal; 20 s timeout)
      └─→ TO_CAVE_ENTRANCE  (traverse 2 entrance waypoints; 60 s/waypoint)
           └─→ EXPLORE       (frontier-based; 420 s total)
                └─→ RETURN_HOME  (navigate to home position; 180 s)
                     └─→ LAND       (descend to 0.4 m; 120 s)
                          └─→ COMPLETE
```

**EXPLORE** is the critical autonomous phase. The state machine subscribes to
`/mapping/global_map` and publishes the `frontier_goal` field directly to `/planning/goal` —
no hardcoded cave waypoints are used, satisfying the project specification. If no valid
frontier is available, the drone falls back to 3 predefined X-axis waypoints (−80, −130,
−200 m) with a 90-second timeout per waypoint. Exploration ends when 4 lanterns are confirmed
by the perception pipeline or the exploration timer expires.

Goals are republished every 2 seconds to prevent the path planner from stalling. A global
1200-second mission timeout forces a transition to `RETURN_HOME` regardless of state. An
external service (`/mission/set_mode`) allows manual override to any state at runtime.

**Dependencies:**
- TF2 (home-position offset correction; Unity scene origin offset subtracted at startup)
- `utils` package (`GlobalMap`, `SetMissionMode`)

**Key Nodes:**

| Node | Package |
|------|---------|
| `mission_state_machine_node` | `state_machine` |

**Key Topics:**

| Topic | Type | Direction |
|-------|------|-----------|
| `/current_state_est` | `nav_msgs/Odometry` | Subscribed |
| `/mapping/global_map` | `utils/GlobalMap` | Subscribed |
| `/perception/lantern_poses` | `utils/LanternPoseArray` | Subscribed |
| `/planning/goal` | `geometry_msgs/PoseStamped` | Published |
| `/mission/state` | `std_msgs/String` | Published |

**Key Services:**

| Service | Type | Description |
|---------|------|-------------|
| `/mission/set_mode` | `utils/SetMissionMode` | Override active state (EXPLORE / RETURN_HOME / LAND / HOLD) |

**Key Parameters:**
- `takeoff_altitude`: 10.0 m
- `cruise_altitude`: 10.0 m
- `land_altitude`: 0.4 m
- `arrival_tolerance`: 8.0 m (tuned for state-estimate drift jumps up to 1.5 m/axis)
- `explore_timeout_s`: 420.0 s
- `return_timeout_s`: 180.0 s
- `land_timeout_s`: 120.0 s
- `mission_hard_timeout_s`: 1200.0 s
- `desired_lantern_count`: 4
- `takeoff_timeout_s`: 20.0 s
- `entrance_timeout_s`: 60.0 s
