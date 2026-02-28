cmake_minimum_required(VERSION 3.10)
project(quadrotor_controller)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_executable(controller_interface_node src/controller_interface_node.cpp)
ament_target_dependencies(
  controller_interface_node
  rclcpp nav_msgs trajectory_msgs std_msgs
)

install(TARGETS controller_interface_node RUNTIME DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})

ament_package()
