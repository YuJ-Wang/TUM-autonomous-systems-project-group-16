# Install script for directory: /home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/install/simulation")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libsocket" TYPE FILE FILES
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./unixdgram.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./exception.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./inetclientdgram.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./libinetsocket.h"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./unixserverstream.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./dgramclient.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./streamclient.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./inetserverstream.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./unixclientdgram.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./socket.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./inetbase.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./inetserverdgram.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./unixclientstream.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./libunixsocket.h"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./select.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./inetclientstream.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./unixbase.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./unixserverdgram.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./inetdgram.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./dgramoverstream.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./framing.hpp"
    "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers/./epoll.hpp"
    )
endif()

