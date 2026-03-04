// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from statemachine_pkg:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/command.hpp"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__COMMAND__STRUCT_HPP_
#define STATEMACHINE_PKG__MSG__DETAIL__COMMAND__STRUCT_HPP_

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
// Member 'target_pos'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__statemachine_pkg__msg__Command __attribute__((deprecated))
#else
# define DEPRECATED__statemachine_pkg__msg__Command __declspec(deprecated)
#endif

namespace statemachine_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Command_
{
  using Type = Command_<ContainerAllocator>;

  explicit Command_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init),
    target_pos(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target = "";
      this->command = 0;
      this->has_target = false;
    }
  }

  explicit Command_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_alloc),
    stamp(_alloc, _init),
    target_pos(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target = "";
      this->command = 0;
      this->has_target = false;
    }
  }

  // field types and members
  using _target_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _target_type target;
  using _command_type =
    uint8_t;
  _command_type command;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _has_target_type =
    bool;
  _has_target_type has_target;
  using _target_pos_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _target_pos_type target_pos;

  // setters for named parameter idiom
  Type & set__target(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->target = _arg;
    return *this;
  }
  Type & set__command(
    const uint8_t & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__has_target(
    const bool & _arg)
  {
    this->has_target = _arg;
    return *this;
  }
  Type & set__target_pos(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->target_pos = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    statemachine_pkg::msg::Command_<ContainerAllocator> *;
  using ConstRawPtr =
    const statemachine_pkg::msg::Command_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<statemachine_pkg::msg::Command_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<statemachine_pkg::msg::Command_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      statemachine_pkg::msg::Command_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<statemachine_pkg::msg::Command_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      statemachine_pkg::msg::Command_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<statemachine_pkg::msg::Command_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<statemachine_pkg::msg::Command_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<statemachine_pkg::msg::Command_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__statemachine_pkg__msg__Command
    std::shared_ptr<statemachine_pkg::msg::Command_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__statemachine_pkg__msg__Command
    std::shared_ptr<statemachine_pkg::msg::Command_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Command_ & other) const
  {
    if (this->target != other.target) {
      return false;
    }
    if (this->command != other.command) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->has_target != other.has_target) {
      return false;
    }
    if (this->target_pos != other.target_pos) {
      return false;
    }
    return true;
  }
  bool operator!=(const Command_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Command_

// alias to use template instance with default allocator
using Command =
  statemachine_pkg::msg::Command_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace statemachine_pkg

#endif  // STATEMACHINE_PKG__MSG__DETAIL__COMMAND__STRUCT_HPP_
