# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket"
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-build"
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix"
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/tmp"
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-stamp"
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src"
  "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-stamp${cfgdir}") # cfgdir has leading slash
endif()
