cmake_minimum_required(VERSION 3.8)
project(perception_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(octomap REQUIRED)
find_package(octomap_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

# Add executable
add_executable(depth_to_pointcloud src/depth_to_pointcloud.cpp)

# Link dependencies
ament_target_dependencies(depth_to_pointcloud
  rclcpp
  sensor_msgs
  geometry_msgs
  cv_bridge
)

target_include_directories(depth_to_pointcloud PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIR}
)

# Add OctoMap executable
add_executable(pointcloud_to_octomap src/pointcloud_to_octomap.cpp)

ament_target_dependencies(pointcloud_to_octomap
  rclcpp
  sensor_msgs
  geometry_msgs
  octomap_msgs
  tf2_ros
  tf2_geometry_msgs
  visualization_msgs
)

target_include_directories(pointcloud_to_octomap PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OCTOMAP_INCLUDE_DIRS}
)

target_link_libraries(pointcloud_to_octomap
  ${OCTOMAP_LIBRARIES}
)

# Add Lantern Detector executable
add_executable(lantern_detector src/lantern_detector.cpp)

ament_target_dependencies(lantern_detector
  rclcpp
  sensor_msgs
  geometry_msgs
  cv_bridge
  tf2_ros
  tf2_geometry_msgs
  visualization_msgs
)

target_include_directories(lantern_detector PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Install executable
install(TARGETS depth_to_pointcloud pointcloud_to_octomap lantern_detector
  DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
