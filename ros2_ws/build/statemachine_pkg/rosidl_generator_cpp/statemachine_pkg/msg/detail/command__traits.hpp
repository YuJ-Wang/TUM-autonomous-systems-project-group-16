// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from statemachine_pkg:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/command.hpp"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__COMMAND__TRAITS_HPP_
#define STATEMACHINE_PKG__MSG__DETAIL__COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "statemachine_pkg/msg/detail/command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'target_pos'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace statemachine_pkg
{

namespace msg
{

inline void to_flow_style_yaml(
  const Command & msg,
  std::ostream & out)
{
  out << "{";
  // member: target
  {
    out << "target: ";
    rosidl_generator_traits::value_to_yaml(msg.target, out);
    out << ", ";
  }

  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: has_target
  {
    out << "has_target: ";
    rosidl_generator_traits::value_to_yaml(msg.has_target, out);
    out << ", ";
  }

  // member: target_pos
  {
    out << "target_pos: ";
    to_flow_style_yaml(msg.target_pos, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Command & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target: ";
    rosidl_generator_traits::value_to_yaml(msg.target, out);
    out << "\n";
  }

  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: has_target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "has_target: ";
    rosidl_generator_traits::value_to_yaml(msg.has_target, out);
    out << "\n";
  }

  // member: target_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_pos:\n";
    to_block_style_yaml(msg.target_pos, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Command & msg, bool use_flow_style = false)
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

}  // namespace statemachine_pkg

namespace rosidl_generator_traits
{

[[deprecated("use statemachine_pkg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const statemachine_pkg::msg::Command & msg,
  std::ostream & out, size_t indentation = 0)
{
  statemachine_pkg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use statemachine_pkg::msg::to_yaml() instead")]]
inline std::string to_yaml(const statemachine_pkg::msg::Command & msg)
{
  return statemachine_pkg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<statemachine_pkg::msg::Command>()
{
  return "statemachine_pkg::msg::Command";
}

template<>
inline const char * name<statemachine_pkg::msg::Command>()
{
  return "statemachine_pkg/msg/Command";
}

template<>
struct has_fixed_size<statemachine_pkg::msg::Command>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<statemachine_pkg::msg::Command>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<statemachine_pkg::msg::Command>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STATEMACHINE_PKG__MSG__DETAIL__COMMAND__TRAITS_HPP_
