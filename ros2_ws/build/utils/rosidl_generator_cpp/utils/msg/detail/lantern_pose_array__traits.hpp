// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose_array.hpp"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__TRAITS_HPP_
#define UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "utils/msg/detail/lantern_pose_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'lanterns'
#include "utils/msg/detail/lantern_pose__traits.hpp"

namespace utils
{

namespace msg
{

inline void to_flow_style_yaml(
  const LanternPoseArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: lanterns
  {
    if (msg.lanterns.size() == 0) {
      out << "lanterns: []";
    } else {
      out << "lanterns: [";
      size_t pending_items = msg.lanterns.size();
      for (auto item : msg.lanterns) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: confirmed_count
  {
    out << "confirmed_count: ";
    rosidl_generator_traits::value_to_yaml(msg.confirmed_count, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LanternPoseArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: lanterns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.lanterns.size() == 0) {
      out << "lanterns: []\n";
    } else {
      out << "lanterns:\n";
      for (auto item : msg.lanterns) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: confirmed_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confirmed_count: ";
    rosidl_generator_traits::value_to_yaml(msg.confirmed_count, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LanternPoseArray & msg, bool use_flow_style = false)
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
  const utils::msg::LanternPoseArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  utils::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use utils::msg::to_yaml() instead")]]
inline std::string to_yaml(const utils::msg::LanternPoseArray & msg)
{
  return utils::msg::to_yaml(msg);
}

template<>
inline const char * data_type<utils::msg::LanternPoseArray>()
{
  return "utils::msg::LanternPoseArray";
}

template<>
inline const char * name<utils::msg::LanternPoseArray>()
{
  return "utils/msg/LanternPoseArray";
}

template<>
struct has_fixed_size<utils::msg::LanternPoseArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<utils::msg::LanternPoseArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<utils::msg::LanternPoseArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__TRAITS_HPP_
