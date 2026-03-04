// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from utils:msg/LanternPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose.hpp"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE__BUILDER_HPP_
#define UTILS__MSG__DETAIL__LANTERN_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "utils/msg/detail/lantern_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace utils
{

namespace msg
{

namespace builder
{

class Init_LanternPose_source_frame
{
public:
  explicit Init_LanternPose_source_frame(::utils::msg::LanternPose & msg)
  : msg_(msg)
  {}
  ::utils::msg::LanternPose source_frame(::utils::msg::LanternPose::_source_frame_type arg)
  {
    msg_.source_frame = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::msg::LanternPose msg_;
};

class Init_LanternPose_confirmed
{
public:
  explicit Init_LanternPose_confirmed(::utils::msg::LanternPose & msg)
  : msg_(msg)
  {}
  Init_LanternPose_source_frame confirmed(::utils::msg::LanternPose::_confirmed_type arg)
  {
    msg_.confirmed = std::move(arg);
    return Init_LanternPose_source_frame(msg_);
  }

private:
  ::utils::msg::LanternPose msg_;
};

class Init_LanternPose_confidence
{
public:
  explicit Init_LanternPose_confidence(::utils::msg::LanternPose & msg)
  : msg_(msg)
  {}
  Init_LanternPose_confirmed confidence(::utils::msg::LanternPose::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_LanternPose_confirmed(msg_);
  }

private:
  ::utils::msg::LanternPose msg_;
};

class Init_LanternPose_pose
{
public:
  explicit Init_LanternPose_pose(::utils::msg::LanternPose & msg)
  : msg_(msg)
  {}
  Init_LanternPose_confidence pose(::utils::msg::LanternPose::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_LanternPose_confidence(msg_);
  }

private:
  ::utils::msg::LanternPose msg_;
};

class Init_LanternPose_id
{
public:
  explicit Init_LanternPose_id(::utils::msg::LanternPose & msg)
  : msg_(msg)
  {}
  Init_LanternPose_pose id(::utils::msg::LanternPose::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_LanternPose_pose(msg_);
  }

private:
  ::utils::msg::LanternPose msg_;
};

class Init_LanternPose_stamp
{
public:
  Init_LanternPose_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LanternPose_id stamp(::utils::msg::LanternPose::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_LanternPose_id(msg_);
  }

private:
  ::utils::msg::LanternPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::msg::LanternPose>()
{
  return utils::msg::builder::Init_LanternPose_stamp();
}

}  // namespace utils

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE__BUILDER_HPP_
