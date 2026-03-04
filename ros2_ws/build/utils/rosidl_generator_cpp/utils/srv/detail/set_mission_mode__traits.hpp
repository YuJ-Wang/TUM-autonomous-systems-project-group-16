// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from utils:srv/SetMissionMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/srv/set_mission_mode.hpp"


#ifndef UTILS__SRV__DETAIL__SET_MISSION_MODE__TRAITS_HPP_
#define UTILS__SRV__DETAIL__SET_MISSION_MODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "utils/srv/detail/set_mission_mode__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace utils
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMissionMode_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: force
  {
    out << "force: ";
    rosidl_generator_traits::value_to_yaml(msg.force, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMissionMode_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: force
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "force: ";
    rosidl_generator_traits::value_to_yaml(msg.force, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMissionMode_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace utils

namespace rosidl_generator_traits
{

[[deprecated("use utils::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const utils::srv::SetMissionMode_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  utils::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use utils::srv::to_yaml() instead")]]
inline std::string to_yaml(const utils::srv::SetMissionMode_Request & msg)
{
  return utils::srv::to_yaml(msg);
}

template<>
inline const char * data_type<utils::srv::SetMissionMode_Request>()
{
  return "utils::srv::SetMissionMode_Request";
}

template<>
inline const char * name<utils::srv::SetMissionMode_Request>()
{
  return "utils/srv/SetMissionMode_Request";
}

template<>
struct has_fixed_size<utils::srv::SetMissionMode_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<utils::srv::SetMissionMode_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<utils::srv::SetMissionMode_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace utils
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMissionMode_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: active_mode
  {
    out << "active_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.active_mode, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMissionMode_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: active_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.active_mode, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMissionMode_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace utils

namespace rosidl_generator_traits
{

[[deprecated("use utils::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const utils::srv::SetMissionMode_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  utils::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use utils::srv::to_yaml() instead")]]
inline std::string to_yaml(const utils::srv::SetMissionMode_Response & msg)
{
  return utils::srv::to_yaml(msg);
}

template<>
inline const char * data_type<utils::srv::SetMissionMode_Response>()
{
  return "utils::srv::SetMissionMode_Response";
}

template<>
inline const char * name<utils::srv::SetMissionMode_Response>()
{
  return "utils/srv/SetMissionMode_Response";
}

template<>
struct has_fixed_size<utils::srv::SetMissionMode_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<utils::srv::SetMissionMode_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<utils::srv::SetMissionMode_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace utils
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMissionMode_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMissionMode_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMissionMode_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace utils

namespace rosidl_generator_traits
{

[[deprecated("use utils::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const utils::srv::SetMissionMode_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  utils::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use utils::srv::to_yaml() instead")]]
inline std::string to_yaml(const utils::srv::SetMissionMode_Event & msg)
{
  return utils::srv::to_yaml(msg);
}

template<>
inline const char * data_type<utils::srv::SetMissionMode_Event>()
{
  return "utils::srv::SetMissionMode_Event";
}

template<>
inline const char * name<utils::srv::SetMissionMode_Event>()
{
  return "utils/srv/SetMissionMode_Event";
}

template<>
struct has_fixed_size<utils::srv::SetMissionMode_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<utils::srv::SetMissionMode_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<utils::srv::SetMissionMode_Request>::value && has_bounded_size<utils::srv::SetMissionMode_Response>::value> {};

template<>
struct is_message<utils::srv::SetMissionMode_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<utils::srv::SetMissionMode>()
{
  return "utils::srv::SetMissionMode";
}

template<>
inline const char * name<utils::srv::SetMissionMode>()
{
  return "utils/srv/SetMissionMode";
}

template<>
struct has_fixed_size<utils::srv::SetMissionMode>
  : std::integral_constant<
    bool,
    has_fixed_size<utils::srv::SetMissionMode_Request>::value &&
    has_fixed_size<utils::srv::SetMissionMode_Response>::value
  >
{
};

template<>
struct has_bounded_size<utils::srv::SetMissionMode>
  : std::integral_constant<
    bool,
    has_bounded_size<utils::srv::SetMissionMode_Request>::value &&
    has_bounded_size<utils::srv::SetMissionMode_Response>::value
  >
{
};

template<>
struct is_service<utils::srv::SetMissionMode>
  : std::true_type
{
};

template<>
struct is_service_request<utils::srv::SetMissionMode_Request>
  : std::true_type
{
};

template<>
struct is_service_response<utils::srv::SetMissionMode_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // UTILS__SRV__DETAIL__SET_MISSION_MODE__TRAITS_HPP_
