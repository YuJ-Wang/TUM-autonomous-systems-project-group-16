// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/answer.hpp"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__ANSWER__STRUCT_HPP_
#define STATEMACHINE_PKG__MSG__DETAIL__ANSWER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__statemachine_pkg__msg__Answer __attribute__((deprecated))
#else
# define DEPRECATED__statemachine_pkg__msg__Answer __declspec(deprecated)
#endif

namespace statemachine_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Answer_
{
  using Type = Answer_<ContainerAllocator>;

  explicit Answer_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node_name = "";
      this->state = 0;
      this->info = "";
    }
  }

  explicit Answer_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : node_name(_alloc),
    info(_alloc),
    timestamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node_name = "";
      this->state = 0;
      this->info = "";
    }
  }

  // field types and members
  using _node_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _node_name_type node_name;
  using _state_type =
    uint8_t;
  _state_type state;
  using _info_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _info_type info;
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__node_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->node_name = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__info(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    statemachine_pkg::msg::Answer_<ContainerAllocator> *;
  using ConstRawPtr =
    const statemachine_pkg::msg::Answer_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      statemachine_pkg::msg::Answer_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      statemachine_pkg::msg::Answer_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__statemachine_pkg__msg__Answer
    std::shared_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__statemachine_pkg__msg__Answer
    std::shared_ptr<statemachine_pkg::msg::Answer_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Answer_ & other) const
  {
    if (this->node_name != other.node_name) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->info != other.info) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const Answer_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Answer_

// alias to use template instance with default allocator
using Answer =
  statemachine_pkg::msg::Answer_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace statemachine_pkg

#endif  // STATEMACHINE_PKG__MSG__DETAIL__ANSWER__STRUCT_HPP_
