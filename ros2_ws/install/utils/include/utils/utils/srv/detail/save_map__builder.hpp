// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from utils:srv/SaveMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/srv/save_map.hpp"


#ifndef UTILS__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
#define UTILS__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "utils/srv/detail/save_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace utils
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Request_file_path
{
public:
  Init_SaveMap_Request_file_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::utils::srv::SaveMap_Request file_path(::utils::srv::SaveMap_Request::_file_path_type arg)
  {
    msg_.file_path = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::srv::SaveMap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::srv::SaveMap_Request>()
{
  return utils::srv::builder::Init_SaveMap_Request_file_path();
}

}  // namespace utils


namespace utils
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Response_message
{
public:
  explicit Init_SaveMap_Response_message(::utils::srv::SaveMap_Response & msg)
  : msg_(msg)
  {}
  ::utils::srv::SaveMap_Response message(::utils::srv::SaveMap_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::srv::SaveMap_Response msg_;
};

class Init_SaveMap_Response_success
{
public:
  Init_SaveMap_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveMap_Response_message success(::utils::srv::SaveMap_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SaveMap_Response_message(msg_);
  }

private:
  ::utils::srv::SaveMap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::srv::SaveMap_Response>()
{
  return utils::srv::builder::Init_SaveMap_Response_success();
}

}  // namespace utils


namespace utils
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Event_response
{
public:
  explicit Init_SaveMap_Event_response(::utils::srv::SaveMap_Event & msg)
  : msg_(msg)
  {}
  ::utils::srv::SaveMap_Event response(::utils::srv::SaveMap_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::srv::SaveMap_Event msg_;
};

class Init_SaveMap_Event_request
{
public:
  explicit Init_SaveMap_Event_request(::utils::srv::SaveMap_Event & msg)
  : msg_(msg)
  {}
  Init_SaveMap_Event_response request(::utils::srv::SaveMap_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SaveMap_Event_response(msg_);
  }

private:
  ::utils::srv::SaveMap_Event msg_;
};

class Init_SaveMap_Event_info
{
public:
  Init_SaveMap_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveMap_Event_request info(::utils::srv::SaveMap_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SaveMap_Event_request(msg_);
  }

private:
  ::utils::srv::SaveMap_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::srv::SaveMap_Event>()
{
  return utils::srv::builder::Init_SaveMap_Event_info();
}

}  // namespace utils

#endif  // UTILS__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
