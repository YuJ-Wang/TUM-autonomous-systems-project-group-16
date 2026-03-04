// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose_array.hpp"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__BUILDER_HPP_
#define UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "utils/msg/detail/lantern_pose_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace utils
{

namespace msg
{

namespace builder
{

class Init_LanternPoseArray_confirmed_count
{
public:
  explicit Init_LanternPoseArray_confirmed_count(::utils::msg::LanternPoseArray & msg)
  : msg_(msg)
  {}
  ::utils::msg::LanternPoseArray confirmed_count(::utils::msg::LanternPoseArray::_confirmed_count_type arg)
  {
    msg_.confirmed_count = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::msg::LanternPoseArray msg_;
};

class Init_LanternPoseArray_lanterns
{
public:
  explicit Init_LanternPoseArray_lanterns(::utils::msg::LanternPoseArray & msg)
  : msg_(msg)
  {}
  Init_LanternPoseArray_confirmed_count lanterns(::utils::msg::LanternPoseArray::_lanterns_type arg)
  {
    msg_.lanterns = std::move(arg);
    return Init_LanternPoseArray_confirmed_count(msg_);
  }

private:
  ::utils::msg::LanternPoseArray msg_;
};

class Init_LanternPoseArray_header
{
public:
  Init_LanternPoseArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LanternPoseArray_lanterns header(::utils::msg::LanternPoseArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LanternPoseArray_lanterns(msg_);
  }

private:
  ::utils::msg::LanternPoseArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::msg::LanternPoseArray>()
{
  return utils::msg::builder::Init_LanternPoseArray_header();
}

}  // namespace utils

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__BUILDER_HPP_
