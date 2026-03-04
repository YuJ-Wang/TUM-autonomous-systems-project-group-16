// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from utils:msg/LanternPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose.hpp"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE__TRAITS_HPP_
#define UTILS__MSG__DETAIL__LANTERN_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "utils/msg/detail/lantern_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace utils
{

namespace msg
{

inline void to_flow_style_yaml(
  const LanternPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: confirmed
  {
    out << "confirmed: ";
    rosidl_generator_traits::value_to_yaml(msg.confirmed, out);
    out << ", ";
  }

  // member: source_frame
  {
    out << "source_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.source_frame, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LanternPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: confirmed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confirmed: ";
    rosidl_generator_traits::value_to_yaml(msg.confirmed, out);
    out << "\n";
  }

  // member: source_frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.source_frame, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LanternPose & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace utils

namespace rosidl_generator_traits
{

[[deprecated("use utils::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const utils::msg::LanternPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  utils::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use utils::msg::to_yaml() instead")]]
inline std::string to_yaml(const utils::msg::LanternPose & msg)
{
  return utils::msg::to_yaml(msg);
}

template<>
inline const char * data_type<utils::msg::LanternPose>()
{
  return "utils::msg::LanternPose";
}

template<>
inline const char * name<utils::msg::LanternPose>()
{
  return "utils/msg/LanternPose";
}

template<>
struct has_fixed_size<utils::msg::LanternPose>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<utils::msg::LanternPose>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<utils::msg::LanternPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE__TRAITS_HPP_
