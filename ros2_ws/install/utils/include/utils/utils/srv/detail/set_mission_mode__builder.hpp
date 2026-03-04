// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from utils:srv/SetMissionMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/srv/set_mission_mode.hpp"


#ifndef UTILS__SRV__DETAIL__SET_MISSION_MODE__BUILDER_HPP_
#define UTILS__SRV__DETAIL__SET_MISSION_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "utils/srv/detail/set_mission_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace utils
{

namespace srv
{

namespace builder
{

class Init_SetMissionMode_Request_force
{
public:
  explicit Init_SetMissionMode_Request_force(::utils::srv::SetMissionMode_Request & msg)
  : msg_(msg)
  {}
  ::utils::srv::SetMissionMode_Request force(::utils::srv::SetMissionMode_Request::_force_type arg)
  {
    msg_.force = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Request msg_;
};

class Init_SetMissionMode_Request_mode
{
public:
  Init_SetMissionMode_Request_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMissionMode_Request_force mode(::utils::srv::SetMissionMode_Request::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_SetMissionMode_Request_force(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::srv::SetMissionMode_Request>()
{
  return utils::srv::builder::Init_SetMissionMode_Request_mode();
}

}  // namespace utils


namespace utils
{

namespace srv
{

namespace builder
{

class Init_SetMissionMode_Response_message
{
public:
  explicit Init_SetMissionMode_Response_message(::utils::srv::SetMissionMode_Response & msg)
  : msg_(msg)
  {}
  ::utils::srv::SetMissionMode_Response message(::utils::srv::SetMissionMode_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Response msg_;
};

class Init_SetMissionMode_Response_active_mode
{
public:
  explicit Init_SetMissionMode_Response_active_mode(::utils::srv::SetMissionMode_Response & msg)
  : msg_(msg)
  {}
  Init_SetMissionMode_Response_message active_mode(::utils::srv::SetMissionMode_Response::_active_mode_type arg)
  {
    msg_.active_mode = std::move(arg);
    return Init_SetMissionMode_Response_message(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Response msg_;
};

class Init_SetMissionMode_Response_success
{
public:
  Init_SetMissionMode_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMissionMode_Response_active_mode success(::utils::srv::SetMissionMode_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetMissionMode_Response_active_mode(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::srv::SetMissionMode_Response>()
{
  return utils::srv::builder::Init_SetMissionMode_Response_success();
}

}  // namespace utils


namespace utils
{

namespace srv
{

namespace builder
{

class Init_SetMissionMode_Event_response
{
public:
  explicit Init_SetMissionMode_Event_response(::utils::srv::SetMissionMode_Event & msg)
  : msg_(msg)
  {}
  ::utils::srv::SetMissionMode_Event response(::utils::srv::SetMissionMode_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Event msg_;
};

class Init_SetMissionMode_Event_request
{
public:
  explicit Init_SetMissionMode_Event_request(::utils::srv::SetMissionMode_Event & msg)
  : msg_(msg)
  {}
  Init_SetMissionMode_Event_response request(::utils::srv::SetMissionMode_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetMissionMode_Event_response(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Event msg_;
};

class Init_SetMissionMode_Event_info
{
public:
  Init_SetMissionMode_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMissionMode_Event_request info(::utils::srv::SetMissionMode_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetMissionMode_Event_request(msg_);
  }

private:
  ::utils::srv::SetMissionMode_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::srv::SetMissionMode_Event>()
{
  return utils::srv::builder::Init_SetMissionMode_Event_info();
}

}  // namespace utils

#endif  // UTILS__SRV__DETAIL__SET_MISSION_MODE__BUILDER_HPP_
