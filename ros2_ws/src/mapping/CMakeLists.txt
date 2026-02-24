cmake_minimum_required(VERSION 3.10)
project(mapping)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(utils REQUIRED)

include_directories(include)

add_executable(voxel_grid_mapper_node src/voxel_grid_mapper_node.cpp)
add_executable(global_map_publisher_node src/global_map_publisher_node.cpp)

ament_target_dependencies(
  voxel_grid_mapper_node
  rclcpp geometry_msgs nav_msgs sensor_msgs std_msgs
  tf2 tf2_ros tf2_geometry_msgs utils
)
ament_target_dependencies(global_map_publisher_node rclcpp std_msgs utils)

install(TARGETS
  voxel_grid_mapper_node
  global_map_publisher_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})

ament_package()
