// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose_array.hpp"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__STRUCT_HPP_
#define UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'lanterns'
#include "utils/msg/detail/lantern_pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__utils__msg__LanternPoseArray __attribute__((deprecated))
#else
# define DEPRECATED__utils__msg__LanternPoseArray __declspec(deprecated)
#endif

namespace utils
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LanternPoseArray_
{
  using Type = LanternPoseArray_<ContainerAllocator>;

  explicit LanternPoseArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->confirmed_count = 0ul;
    }
  }

  explicit LanternPoseArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->confirmed_count = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _lanterns_type =
    std::vector<utils::msg::LanternPose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<utils::msg::LanternPose_<ContainerAllocator>>>;
  _lanterns_type lanterns;
  using _confirmed_count_type =
    uint32_t;
  _confirmed_count_type confirmed_count;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__lanterns(
    const std::vector<utils::msg::LanternPose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<utils::msg::LanternPose_<ContainerAllocator>>> & _arg)
  {
    this->lanterns = _arg;
    return *this;
  }
  Type & set__confirmed_count(
    const uint32_t & _arg)
  {
    this->confirmed_count = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    utils::msg::LanternPoseArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const utils::msg::LanternPoseArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<utils::msg::LanternPoseArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<utils::msg::LanternPoseArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      utils::msg::LanternPoseArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<utils::msg::LanternPoseArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      utils::msg::LanternPoseArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<utils::msg::LanternPoseArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<utils::msg::LanternPoseArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<utils::msg::LanternPoseArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__utils__msg__LanternPoseArray
    std::shared_ptr<utils::msg::LanternPoseArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__utils__msg__LanternPoseArray
    std::shared_ptr<utils::msg::LanternPoseArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LanternPoseArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->lanterns != other.lanterns) {
      return false;
    }
    if (this->confirmed_count != other.confirmed_count) {
      return false;
    }
    return true;
  }
  bool operator!=(const LanternPoseArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LanternPoseArray_

// alias to use template instance with default allocator
using LanternPoseArray =
  utils::msg::LanternPoseArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace utils

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__STRUCT_HPP_
