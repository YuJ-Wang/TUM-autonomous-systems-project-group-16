// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from statemachine_pkg:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/command.hpp"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__COMMAND__BUILDER_HPP_
#define STATEMACHINE_PKG__MSG__DETAIL__COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "statemachine_pkg/msg/detail/command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace statemachine_pkg
{

namespace msg
{

namespace builder
{

class Init_Command_target_pos
{
public:
  explicit Init_Command_target_pos(::statemachine_pkg::msg::Command & msg)
  : msg_(msg)
  {}
  ::statemachine_pkg::msg::Command target_pos(::statemachine_pkg::msg::Command::_target_pos_type arg)
  {
    msg_.target_pos = std::move(arg);
    return std::move(msg_);
  }

private:
  ::statemachine_pkg::msg::Command msg_;
};

class Init_Command_has_target
{
public:
  explicit Init_Command_has_target(::statemachine_pkg::msg::Command & msg)
  : msg_(msg)
  {}
  Init_Command_target_pos has_target(::statemachine_pkg::msg::Command::_has_target_type arg)
  {
    msg_.has_target = std::move(arg);
    return Init_Command_target_pos(msg_);
  }

private:
  ::statemachine_pkg::msg::Command msg_;
};

class Init_Command_stamp
{
public:
  explicit Init_Command_stamp(::statemachine_pkg::msg::Command & msg)
  : msg_(msg)
  {}
  Init_Command_has_target stamp(::statemachine_pkg::msg::Command::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Command_has_target(msg_);
  }

private:
  ::statemachine_pkg::msg::Command msg_;
};

class Init_Command_command
{
public:
  explicit Init_Command_command(::statemachine_pkg::msg::Command & msg)
  : msg_(msg)
  {}
  Init_Command_stamp command(::statemachine_pkg::msg::Command::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_Command_stamp(msg_);
  }

private:
  ::statemachine_pkg::msg::Command msg_;
};

class Init_Command_target
{
public:
  Init_Command_target()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Command_command target(::statemachine_pkg::msg::Command::_target_type arg)
  {
    msg_.target = std::move(arg);
    return Init_Command_command(msg_);
  }

private:
  ::statemachine_pkg::msg::Command msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::statemachine_pkg::msg::Command>()
{
  return statemachine_pkg::msg::builder::Init_Command_target();
}

}  // namespace statemachine_pkg

#endif  // STATEMACHINE_PKG__MSG__DETAIL__COMMAND__BUILDER_HPP_
