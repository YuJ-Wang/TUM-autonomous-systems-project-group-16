set(libsocket_INCLUDE_DIRS "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket/headers")

set(libsocket_BINARY_DIR "/home/wangyujia/Autonome_Systeme/new/autosys13/ros2_ws/build/simulation/libsocket-prefix/src/libsocket-build")

include(${libsocket_BINARY_DIR}/libsocketTargets.cmake)

set(libsocket_LIBRARIES socket++)
