#!/bin/bash
# Installation script for AutonomousSystems2025 SubTerrain Challenge
# This script installs all required dependencies for the project

set -e  # Exit on error

echo "=================================================="
echo "Installing dependencies for SubTerrain Challenge"
echo "=================================================="

# Check if running Ubuntu 24.04
if [ -f /etc/os-release ]; then
    . /etc/os-release
    if [ "$VERSION_ID" != "24.04" ]; then
        echo "Warning: This project is designed for Ubuntu 24.04. You are running $VERSION_ID"
        read -p "Continue anyway? (y/n) " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            exit 1
        fi
    fi
fi

echo ""
echo "Step 1: Updating package lists..."
sudo apt update

echo ""
echo "Step 2: Installing ROS2 Jazzy dependencies..."
sudo apt install -y \
    ros-jazzy-cv-bridge \
    ros-jazzy-vision-opencv \
    ros-jazzy-octomap \
    ros-jazzy-octomap-msgs \
    ros-jazzy-octomap-ros \
    ros-jazzy-tf2-ros \
    ros-jazzy-tf2-geometry-msgs \
    ros-jazzy-visualization-msgs

echo ""
echo "Step 3: Installing system dependencies..."
sudo apt install -y \
    libeigen3-dev \
    build-essential \
    cmake \
    git

echo ""
echo "Step 4: Checking ROS2 Jazzy installation..."
if [ ! -f /opt/ros/jazzy/setup.bash ]; then
    echo "ERROR: ROS2 Jazzy is not installed!"
    echo "Please install ROS2 Jazzy first: https://docs.ros.org/en/jazzy/Installation.html"
    exit 1
fi

echo ""
echo "=================================================="
echo "✅ All dependencies installed successfully!"
echo "=================================================="
echo ""
echo "Next steps:"
echo "1. Build the workspace:"
echo "   cd ros2_ws"
echo "   colcon build"
echo "   source install/setup.bash"
echo ""
echo "2. Make start_rviz2.sh executable:"
echo "   chmod +x start_rviz2.sh"
echo ""
echo "3. Follow README.md to run the simulation"
echo "=================================================="
