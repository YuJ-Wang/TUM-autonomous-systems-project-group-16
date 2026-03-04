// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/answer.hpp"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__ANSWER__TRAITS_HPP_
#define STATEMACHINE_PKG__MSG__DETAIL__ANSWER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "statemachine_pkg/msg/detail/answer__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace statemachine_pkg
{

namespace msg
{

inline void to_flow_style_yaml(
  const Answer & msg,
  std::ostream & out)
{
  out << "{";
  // member: node_name
  {
    out << "node_name: ";
    rosidl_generator_traits::value_to_yaml(msg.node_name, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: info
  {
    out << "info: ";
    rosidl_generator_traits::value_to_yaml(msg.info, out);
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Answer & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: node_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "node_name: ";
    rosidl_generator_traits::value_to_yaml(msg.node_name, out);
    out << "\n";
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info: ";
    rosidl_generator_traits::value_to_yaml(msg.info, out);
    out << "\n";
  }

  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp:\n";
    to_block_style_yaml(msg.timestamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Answer & msg, bool use_flow_style = false)
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
  const statemachine_pkg::msg::Answer & msg,
  std::ostream & out, size_t indentation = 0)
{
  statemachine_pkg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use statemachine_pkg::msg::to_yaml() instead")]]
inline std::string to_yaml(const statemachine_pkg::msg::Answer & msg)
{
  return statemachine_pkg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<statemachine_pkg::msg::Answer>()
{
  return "statemachine_pkg::msg::Answer";
}

template<>
inline const char * name<statemachine_pkg::msg::Answer>()
{
  return "statemachine_pkg/msg/Answer";
}

template<>
struct has_fixed_size<statemachine_pkg::msg::Answer>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<statemachine_pkg::msg::Answer>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<statemachine_pkg::msg::Answer>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STATEMACHINE_PKG__MSG__DETAIL__ANSWER__TRAITS_HPP_
