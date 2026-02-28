cmake_minimum_required(VERSION 3.10)
project(utils)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/LanternPose.msg"
  "msg/LanternPoseArray.msg"
  "msg/GlobalMap.msg"
  "srv/SetMissionMode.srv"
  "srv/SaveMap.srv"
  DEPENDENCIES std_msgs geometry_msgs builtin_interfaces
)

include_directories(include)

add_executable(utils_node src/utils_node.cpp)
ament_target_dependencies(utils_node rclcpp std_msgs geometry_msgs)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(utils_node "${cpp_typesupport_target}")

install(TARGETS utils_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config msg srv
  DESTINATION share/${PROJECT_NAME}
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
