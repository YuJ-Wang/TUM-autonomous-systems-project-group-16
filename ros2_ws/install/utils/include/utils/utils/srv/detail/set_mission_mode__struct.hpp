// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from utils:srv/SetMissionMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/srv/set_mission_mode.hpp"


#ifndef UTILS__SRV__DETAIL__SET_MISSION_MODE__STRUCT_HPP_
#define UTILS__SRV__DETAIL__SET_MISSION_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__utils__srv__SetMissionMode_Request __attribute__((deprecated))
#else
# define DEPRECATED__utils__srv__SetMissionMode_Request __declspec(deprecated)
#endif

namespace utils
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetMissionMode_Request_
{
  using Type = SetMissionMode_Request_<ContainerAllocator>;

  explicit SetMissionMode_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = "";
      this->force = false;
    }
  }

  explicit SetMissionMode_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : mode(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = "";
      this->force = false;
    }
  }

  // field types and members
  using _mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mode_type mode;
  using _force_type =
    bool;
  _force_type force;

  // setters for named parameter idiom
  Type & set__mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__force(
    const bool & _arg)
  {
    this->force = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    utils::srv::SetMissionMode_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const utils::srv::SetMissionMode_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      utils::srv::SetMissionMode_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      utils::srv::SetMissionMode_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__utils__srv__SetMissionMode_Request
    std::shared_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__utils__srv__SetMissionMode_Request
    std::shared_ptr<utils::srv::SetMissionMode_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetMissionMode_Request_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->force != other.force) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetMissionMode_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetMissionMode_Request_

// alias to use template instance with default allocator
using SetMissionMode_Request =
  utils::srv::SetMissionMode_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace utils


#ifndef _WIN32
# define DEPRECATED__utils__srv__SetMissionMode_Response __attribute__((deprecated))
#else
# define DEPRECATED__utils__srv__SetMissionMode_Response __declspec(deprecated)
#endif

namespace utils
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetMissionMode_Response_
{
  using Type = SetMissionMode_Response_<ContainerAllocator>;

  explicit SetMissionMode_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->active_mode = "";
      this->message = "";
    }
  }

  explicit SetMissionMode_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : active_mode(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->active_mode = "";
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _active_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _active_mode_type active_mode;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__active_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->active_mode = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    utils::srv::SetMissionMode_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const utils::srv::SetMissionMode_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      utils::srv::SetMissionMode_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      utils::srv::SetMissionMode_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__utils__srv__SetMissionMode_Response
    std::shared_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__utils__srv__SetMissionMode_Response
    std::shared_ptr<utils::srv::SetMissionMode_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetMissionMode_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->active_mode != other.active_mode) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetMissionMode_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetMissionMode_Response_

// alias to use template instance with default allocator
using SetMissionMode_Response =
  utils::srv::SetMissionMode_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace utils


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__utils__srv__SetMissionMode_Event __attribute__((deprecated))
#else
# define DEPRECATED__utils__srv__SetMissionMode_Event __declspec(deprecated)
#endif

namespace utils
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetMissionMode_Event_
{
  using Type = SetMissionMode_Event_<ContainerAllocator>;

  explicit SetMissionMode_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit SetMissionMode_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<utils::srv::SetMissionMode_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<utils::srv::SetMissionMode_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<utils::srv::SetMissionMode_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<utils::srv::SetMissionMode_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<utils::srv::SetMissionMode_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<utils::srv::SetMissionMode_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<utils::srv::SetMissionMode_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<utils::srv::SetMissionMode_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    utils::srv::SetMissionMode_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const utils::srv::SetMissionMode_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      utils::srv::SetMissionMode_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      utils::srv::SetMissionMode_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__utils__srv__SetMissionMode_Event
    std::shared_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__utils__srv__SetMissionMode_Event
    std::shared_ptr<utils::srv::SetMissionMode_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetMissionMode_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetMissionMode_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetMissionMode_Event_

// alias to use template instance with default allocator
using SetMissionMode_Event =
  utils::srv::SetMissionMode_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace utils

namespace utils
{

namespace srv
{

struct SetMissionMode
{
  using Request = utils::srv::SetMissionMode_Request;
  using Response = utils::srv::SetMissionMode_Response;
  using Event = utils::srv::SetMissionMode_Event;
};

}  // namespace srv

}  // namespace utils

#endif  // UTILS__SRV__DETAIL__SET_MISSION_MODE__STRUCT_HPP_
