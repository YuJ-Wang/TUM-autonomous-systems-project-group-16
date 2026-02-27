#!/usr/bin/env python3
"""
Automatic waypoint navigation for drone
Moves drone through predefined waypoints to explore the cave
"""

import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import MultiDOFJointTrajectory, MultiDOFJointTrajectoryPoint
from geometry_msgs.msg import Transform, Twist, PoseStamped
import math
import time

class DroneWaypointNavigator(Node):
    def __init__(self):
        super().__init__('drone_waypoint_navigator')
        
        # Publisher for trajectory commands
        self.trajectory_pub = self.create_publisher(
            MultiDOFJointTrajectory,
            '/command_topic',
            10
        )
        
        # Subscribe to current pose
        self.pose_sub = self.create_subscription(
            PoseStamped,
            '/true_pose',
            self.pose_callback,
            10
        )
        
        # Current position
        self.current_x = 0.0
        self.current_y = 0.0
        self.current_z = 0.0
        self.pose_received = False
        self.start_x = None
        self.start_y = None
        self.start_z = None
        
        # Relative waypoints will be set after getting initial pose
        self.waypoints = []
        self.waypoints_set = False
        
        self.current_waypoint_idx = 0
        self.waypoint_reached_threshold = 0.3  # meters
        
        # Timer for sending commands
        self.timer = self.create_timer(0.5, self.navigation_loop)
        
        self.get_logger().info("Drone Waypoint Navigator Started")
        self.get_logger().info(f"Total waypoints: {len(self.waypoints)}")
        
    def pose_callback(self, msg):
        """Update current position"""
        self.current_x = msg.pose.position.x
        self.current_y = msg.pose.position.y
        self.current_z = msg.pose.position.z
        
        # Set initial position and create relative waypoints
        if not self.pose_received:
            self.start_x = self.current_x
            self.start_y = self.current_y
            self.start_z = self.current_z
            
            # Define waypoints relative to starting position
            # Format: (forward, left, up, yaw)
            relative_waypoints = [
                (0, 0, 0, 0.0),       # Hold current position
                (2, 0, 0, 0.0),       # Move forward 2m
                (4, 0, 0, 0.0),       # Move forward 4m
                (6, 0, 0, 0.0),       # Move forward 6m
                (6, 2, 0, 0.0),       # Move forward 6m, left 2m
                (6, 4, 0, 0.0),       # Move forward 6m, left 4m
                (8, 4, 0, 0.0),       # Move forward 8m, left 4m
                (10, 4, 0, 0.0),      # Move forward 10m, left 4m
            ]
            
            # Convert relative to absolute coordinates
            for rel in relative_waypoints:
                abs_x = self.start_x + rel[0]
                abs_y = self.start_y + rel[1]
                abs_z = self.start_z + rel[2]
                yaw = rel[3]
                self.waypoints.append((abs_x, abs_y, abs_z, yaw))
            
            self.waypoints_set = True
            self.get_logger().info(f"Starting position: ({self.start_x:.1f}, {self.start_y:.1f}, {self.start_z:.1f})")
            self.get_logger().info(f"Created {len(self.waypoints)} waypoints")
            
        self.pose_received = True
        
    def distance_to_waypoint(self, waypoint):
        """Calculate distance to target waypoint"""
        dx = waypoint[0] - self.current_x
        dy = waypoint[1] - self.current_y
        dz = waypoint[2] - self.current_z
        return math.sqrt(dx*dx + dy*dy + dz*dz)
        
    def send_waypoint_command(self, x, y, z, yaw):
        """Send waypoint command to drone"""
        msg = MultiDOFJointTrajectory()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "world"
        msg.joint_names = ['base_link']
        
        point = MultiDOFJointTrajectoryPoint()
        
        # Set desired transform
        transform = Transform()
        transform.translation.x = x
        transform.translation.y = y
        transform.translation.z = z
        
        # Convert yaw to quaternion
        transform.rotation.w = math.cos(yaw / 2.0)
        transform.rotation.x = 0.0
        transform.rotation.y = 0.0
        transform.rotation.z = math.sin(yaw / 2.0)
        
        point.transforms.append(transform)
        
        # Set velocities to zero for smooth movement
        velocity = Twist()
        velocity.linear.x = 0.0
        velocity.linear.y = 0.0
        velocity.linear.z = 0.0
        velocity.angular.x = 0.0
        velocity.angular.y = 0.0
        velocity.angular.z = 0.0
        point.velocities.append(velocity)
        
        # Set time from start
        point.time_from_start.sec = 2
        point.time_from_start.nanosec = 0
        
        msg.points.append(point)
        
        self.trajectory_pub.publish(msg)
        
    def navigation_loop(self):
        """Main navigation loop"""
        if not self.pose_received:
            self.get_logger().warn("Waiting for pose data...", throttle_duration_sec=2.0)
            return
            
        # Check if all waypoints completed
        if self.current_waypoint_idx >= len(self.waypoints):
            self.get_logger().info("All waypoints reached! Navigation complete.", throttle_duration_sec=5.0)
            return
            
        # Get current target waypoint
        waypoint = self.waypoints[self.current_waypoint_idx]
        
        # Calculate distance to waypoint
        distance = self.distance_to_waypoint(waypoint)
        
        # Check if waypoint reached
        if distance < self.waypoint_reached_threshold:
            self.get_logger().info(f"Waypoint {self.current_waypoint_idx + 1}/{len(self.waypoints)} reached!")
            self.current_waypoint_idx += 1
            
            if self.current_waypoint_idx < len(self.waypoints):
                next_waypoint = self.waypoints[self.current_waypoint_idx]
                self.get_logger().info(f"Moving to waypoint {self.current_waypoint_idx + 1}: "
                                     f"({next_waypoint[0]:.1f}, {next_waypoint[1]:.1f}, {next_waypoint[2]:.1f})")
        else:
            # Send command to current waypoint
            self.send_waypoint_command(waypoint[0], waypoint[1], waypoint[2], waypoint[3])
            self.get_logger().info(f"Moving to waypoint {self.current_waypoint_idx + 1}: "
                                 f"distance = {distance:.2f}m", 
                                 throttle_duration_sec=2.0)

def main(args=None):
    rclpy.init(args=args)
    navigator = DroneWaypointNavigator()
    
    try:
        rclpy.spin(navigator)
    except KeyboardInterrupt:
        navigator.get_logger().info("Navigation stopped by user")
    
    navigator.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
