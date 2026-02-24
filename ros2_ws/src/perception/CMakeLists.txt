cmake_minimum_required(VERSION 3.10)
project(perception)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

include_directories(include)

add_executable(light_detection_node src/light_detection.cpp)
ament_target_dependencies(
  light_detection_node
  rclcpp sensor_msgs geometry_msgs cv_bridge tf2 tf2_ros tf2_geometry_msgs
)
target_link_libraries(light_detection_node ${OpenCV_LIBRARIES})

install(TARGETS light_detection_node RUNTIME DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})

ament_package()
