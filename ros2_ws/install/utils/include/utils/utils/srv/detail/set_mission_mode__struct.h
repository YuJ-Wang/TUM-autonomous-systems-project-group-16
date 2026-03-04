// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from utils:srv/SetMissionMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/srv/set_mission_mode.h"


#ifndef UTILS__SRV__DETAIL__SET_MISSION_MODE__STRUCT_H_
#define UTILS__SRV__DETAIL__SET_MISSION_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'mode'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetMissionMode in the package utils.
typedef struct utils__srv__SetMissionMode_Request
{
  rosidl_runtime_c__String mode;
  bool force;
} utils__srv__SetMissionMode_Request;

// Struct for a sequence of utils__srv__SetMissionMode_Request.
typedef struct utils__srv__SetMissionMode_Request__Sequence
{
  utils__srv__SetMissionMode_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__srv__SetMissionMode_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'active_mode'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetMissionMode in the package utils.
typedef struct utils__srv__SetMissionMode_Response
{
  bool success;
  rosidl_runtime_c__String active_mode;
  rosidl_runtime_c__String message;
} utils__srv__SetMissionMode_Response;

// Struct for a sequence of utils__srv__SetMissionMode_Response.
typedef struct utils__srv__SetMissionMode_Response__Sequence
{
  utils__srv__SetMissionMode_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__srv__SetMissionMode_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  utils__srv__SetMissionMode_Event__request__MAX_SIZE = 1
};
// response
enum
{
  utils__srv__SetMissionMode_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetMissionMode in the package utils.
typedef struct utils__srv__SetMissionMode_Event
{
  service_msgs__msg__ServiceEventInfo info;
  utils__srv__SetMissionMode_Request__Sequence request;
  utils__srv__SetMissionMode_Response__Sequence response;
} utils__srv__SetMissionMode_Event;

// Struct for a sequence of utils__srv__SetMissionMode_Event.
typedef struct utils__srv__SetMissionMode_Event__Sequence
{
  utils__srv__SetMissionMode_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__srv__SetMissionMode_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UTILS__SRV__DETAIL__SET_MISSION_MODE__STRUCT_H_
