// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/answer.hpp"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__ANSWER__BUILDER_HPP_
#define STATEMACHINE_PKG__MSG__DETAIL__ANSWER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "statemachine_pkg/msg/detail/answer__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace statemachine_pkg
{

namespace msg
{

namespace builder
{

class Init_Answer_timestamp
{
public:
  explicit Init_Answer_timestamp(::statemachine_pkg::msg::Answer & msg)
  : msg_(msg)
  {}
  ::statemachine_pkg::msg::Answer timestamp(::statemachine_pkg::msg::Answer::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::statemachine_pkg::msg::Answer msg_;
};

class Init_Answer_info
{
public:
  explicit Init_Answer_info(::statemachine_pkg::msg::Answer & msg)
  : msg_(msg)
  {}
  Init_Answer_timestamp info(::statemachine_pkg::msg::Answer::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Answer_timestamp(msg_);
  }

private:
  ::statemachine_pkg::msg::Answer msg_;
};

class Init_Answer_state
{
public:
  explicit Init_Answer_state(::statemachine_pkg::msg::Answer & msg)
  : msg_(msg)
  {}
  Init_Answer_info state(::statemachine_pkg::msg::Answer::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_Answer_info(msg_);
  }

private:
  ::statemachine_pkg::msg::Answer msg_;
};

class Init_Answer_node_name
{
public:
  Init_Answer_node_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Answer_state node_name(::statemachine_pkg::msg::Answer::_node_name_type arg)
  {
    msg_.node_name = std::move(arg);
    return Init_Answer_state(msg_);
  }

private:
  ::statemachine_pkg::msg::Answer msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::statemachine_pkg::msg::Answer>()
{
  return statemachine_pkg::msg::builder::Init_Answer_node_name();
}

}  // namespace statemachine_pkg

#endif  // STATEMACHINE_PKG__MSG__DETAIL__ANSWER__BUILDER_HPP_
