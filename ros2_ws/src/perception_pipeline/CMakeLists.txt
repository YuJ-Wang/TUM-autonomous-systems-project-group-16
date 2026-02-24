cmake_minimum_required(VERSION 3.10)
project(perception_pipeline)

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
find_package(utils REQUIRED)

include_directories(include)

add_executable(semantic_camera_subscriber_node src/semantic_camera_subscriber_node.cpp)
add_executable(depth_to_pointcloud_node src/depth_to_pointcloud_node.cpp)
add_executable(object_detection_node src/object_detection_node.cpp)

ament_target_dependencies(semantic_camera_subscriber_node rclcpp sensor_msgs cv_bridge)
ament_target_dependencies(depth_to_pointcloud_node rclcpp sensor_msgs cv_bridge)
ament_target_dependencies(
  object_detection_node
  rclcpp sensor_msgs geometry_msgs cv_bridge tf2 tf2_ros tf2_geometry_msgs utils
)

target_link_libraries(semantic_camera_subscriber_node ${OpenCV_LIBRARIES})
target_link_libraries(depth_to_pointcloud_node ${OpenCV_LIBRARIES})
target_link_libraries(object_detection_node ${OpenCV_LIBRARIES})

install(TARGETS
  semantic_camera_subscriber_node
  depth_to_pointcloud_node
  object_detection_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})

ament_package()
