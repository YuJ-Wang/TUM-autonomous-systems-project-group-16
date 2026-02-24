cmake_minimum_required(VERSION 3.10)
project(state_machine)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(utils REQUIRED)

include_directories(include)

add_executable(mission_state_machine_node src/mission_state_machine_node.cpp)
ament_target_dependencies(
  mission_state_machine_node
  rclcpp nav_msgs geometry_msgs std_msgs tf2 tf2_geometry_msgs utils
)

install(TARGETS mission_state_machine_node RUNTIME DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})

ament_package()
