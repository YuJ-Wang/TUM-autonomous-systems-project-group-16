set(libsocket_INCLUDE_DIRS "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers")

set(libsocket_BINARY_DIR "/home/jiacheng/autonomoussystems2025/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-build")

include(${libsocket_BINARY_DIR}/libsocketTargets.cmake)

set(libsocket_LIBRARIES socket++)
