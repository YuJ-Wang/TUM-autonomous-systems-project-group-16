cmake_minimum_required(VERSION 3.10)
project(path_planner)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(utils REQUIRED)

include_directories(include)

add_executable(path_planner_node src/path_planner_node.cpp)
ament_target_dependencies(
  path_planner_node
  rclcpp nav_msgs geometry_msgs std_msgs utils
)

install(TARGETS path_planner_node RUNTIME DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})

ament_package()
