#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "unity_stream_parser.h"
#include "rgb_camera_parser.h"
#include "depth_camera_parser.h"
#include "fisheye_camera_parser.h"
#include "imu_parser.h"
#include "true_state_parser.h"
#include "unity_command_stream.h"


int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("unity_ros");

  // Retry binding port 9998 — a previous instance may still be releasing the port.
  RCLCPP_INFO(node->get_logger(), "Starting TCPStreamReader (server on port 9998)");
  std::unique_ptr<TCPStreamReader> stream_reader_ptr;
  for (int attempt = 1; attempt <= 30; ++attempt) {
    try {
      stream_reader_ptr = std::make_unique<TCPStreamReader>("127.0.0.1", "9998");
      break;
    } catch (const libsocket::socket_exception & e) {
      RCLCPP_WARN(node->get_logger(),
        "Port 9998 not available (attempt %d/30): %s — retrying in 1 s", attempt, e.mesg.c_str());
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  if (!stream_reader_ptr) {
    RCLCPP_FATAL(node->get_logger(), "Could not bind port 9998 after 30 attempts — aborting.");
    rclcpp::shutdown();
    return 1;
  }
  TCPStreamReader & stream_reader = *stream_reader_ptr;

  RCLCPP_INFO(node->get_logger(), "Waiting for Unity to connect on port 9998...");
  stream_reader.WaitConnect();
  RCLCPP_INFO(node->get_logger(), "Unity connected — starting command stream");

  IMUParser imu_parser;

  // Retry connecting to Unity command port 9999 — Unity may not be ready yet.
  std::unique_ptr<UnityCommandStream> command_stream_ptr;
  for (int attempt = 1; attempt <= 30; ++attempt) {
    try {
      command_stream_ptr = std::make_unique<UnityCommandStream>("127.0.0.1", "9999");
      break;
    } catch (const libsocket::socket_exception & e) {
      RCLCPP_WARN(node->get_logger(),
        "Unity port 9999 not ready (attempt %d/30): %s — retrying in 1 s", attempt, e.mesg.c_str());
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  if (!command_stream_ptr) {
    RCLCPP_FATAL(node->get_logger(), "Could not connect to Unity port 9999 after 30 attempts — aborting.");
    rclcpp::shutdown();
    return 1;
  }
  UnityCommandStream & command_stream = *command_stream_ptr;

  std::vector<std::shared_ptr<UnityStreamParser>> stream_parsers(UnityMessageType::MESSAGE_TYPE_COUNT);

  stream_parsers[UnityMessageType::UNITY_STATE] = std::make_shared<TrueStateParser>();
  stream_parsers[UnityMessageType::UNITY_IMU] = std::make_shared<IMUParser>();
  stream_parsers[UnityMessageType::UNITY_CAMERA] = std::make_shared<RGBCameraParser>();
  stream_parsers[UnityMessageType::UNITY_DEPTH] = std::make_shared<DepthCameraParser>();
  stream_parsers[UnityMessageType::UNITY_FISHEYE] = std::make_shared<FisheyeCameraParser>();
  
  while (stream_reader.Good() && rclcpp::ok()) {    
    uint32_t magic = stream_reader.ReadUInt();


    if(magic == 0xDEADC0DE) {
      double ros_time = node->now().seconds();
      UnityHeader header;
      header.type = static_cast<UnityMessageType>(stream_reader.ReadUInt());
      uint64_t timestamp_raw = stream_reader.ReadUInt64();
      header.timestamp = static_cast<double>(timestamp_raw) * 1e-7;
      header.name = stream_reader.ReadString();
      
      if(header.type < UnityMessageType::MESSAGE_TYPE_COUNT) {
        stream_parsers[header.type]->ParseMessage(header, stream_reader);
      }
    } else {
      RCLCPP_ERROR(node->get_logger(), "Stream corrupted, could not parse unity message");
    }

    rclcpp::spin_some(node);
  }

  rclcpp::shutdown();
  return 0;
}
