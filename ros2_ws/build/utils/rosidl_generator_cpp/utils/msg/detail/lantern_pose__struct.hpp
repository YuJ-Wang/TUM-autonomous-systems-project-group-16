// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from utils:msg/LanternPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose.hpp"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE__STRUCT_HPP_
#define UTILS__MSG__DETAIL__LANTERN_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__utils__msg__LanternPose __attribute__((deprecated))
#else
# define DEPRECATED__utils__msg__LanternPose __declspec(deprecated)
#endif

namespace utils
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LanternPose_
{
  using Type = LanternPose_<ContainerAllocator>;

  explicit LanternPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init),
    pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0ul;
      this->confidence = 0.0f;
      this->confirmed = false;
      this->source_frame = "";
    }
  }

  explicit LanternPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    pose(_alloc, _init),
    source_frame(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0ul;
      this->confidence = 0.0f;
      this->confirmed = false;
      this->source_frame = "";
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _id_type =
    uint32_t;
  _id_type id;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _confirmed_type =
    bool;
  _confirmed_type confirmed;
  using _source_frame_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_frame_type source_frame;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__id(
    const uint32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__confirmed(
    const bool & _arg)
  {
    this->confirmed = _arg;
    return *this;
  }
  Type & set__source_frame(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source_frame = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    utils::msg::LanternPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const utils::msg::LanternPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<utils::msg::LanternPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<utils::msg::LanternPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      utils::msg::LanternPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<utils::msg::LanternPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      utils::msg::LanternPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<utils::msg::LanternPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<utils::msg::LanternPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<utils::msg::LanternPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__utils__msg__LanternPose
    std::shared_ptr<utils::msg::LanternPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__utils__msg__LanternPose
    std::shared_ptr<utils::msg::LanternPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LanternPose_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->confirmed != other.confirmed) {
      return false;
    }
    if (this->source_frame != other.source_frame) {
      return false;
    }
    return true;
  }
  bool operator!=(const LanternPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LanternPose_

// alias to use template instance with default allocator
using LanternPose =
  utils::msg::LanternPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace utils

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE__STRUCT_HPP_
