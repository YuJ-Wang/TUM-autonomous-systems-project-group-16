// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from utils:srv/SaveMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/srv/save_map.h"


#ifndef UTILS__SRV__DETAIL__SAVE_MAP__STRUCT_H_
#define UTILS__SRV__DETAIL__SAVE_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'file_path'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SaveMap in the package utils.
typedef struct utils__srv__SaveMap_Request
{
  rosidl_runtime_c__String file_path;
} utils__srv__SaveMap_Request;

// Struct for a sequence of utils__srv__SaveMap_Request.
typedef struct utils__srv__SaveMap_Request__Sequence
{
  utils__srv__SaveMap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__srv__SaveMap_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SaveMap in the package utils.
typedef struct utils__srv__SaveMap_Response
{
  bool success;
  rosidl_runtime_c__String message;
} utils__srv__SaveMap_Response;

// Struct for a sequence of utils__srv__SaveMap_Response.
typedef struct utils__srv__SaveMap_Response__Sequence
{
  utils__srv__SaveMap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__srv__SaveMap_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  utils__srv__SaveMap_Event__request__MAX_SIZE = 1
};
// response
enum
{
  utils__srv__SaveMap_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SaveMap in the package utils.
typedef struct utils__srv__SaveMap_Event
{
  service_msgs__msg__ServiceEventInfo info;
  utils__srv__SaveMap_Request__Sequence request;
  utils__srv__SaveMap_Response__Sequence response;
} utils__srv__SaveMap_Event;

// Struct for a sequence of utils__srv__SaveMap_Event.
typedef struct utils__srv__SaveMap_Event__Sequence
{
  utils__srv__SaveMap_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__srv__SaveMap_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UTILS__SRV__DETAIL__SAVE_MAP__STRUCT_H_
