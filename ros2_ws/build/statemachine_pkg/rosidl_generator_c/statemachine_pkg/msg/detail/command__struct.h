// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from statemachine_pkg:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/command.h"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__COMMAND__STRUCT_H_
#define STATEMACHINE_PKG__MSG__DETAIL__COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'target'
#include "rosidl_runtime_c/string.h"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'target_pos'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Command in the package statemachine_pkg.
typedef struct statemachine_pkg__msg__Command
{
  rosidl_runtime_c__String target;
  uint8_t command;
  builtin_interfaces__msg__Time stamp;
  bool has_target;
  geometry_msgs__msg__Point target_pos;
} statemachine_pkg__msg__Command;

// Struct for a sequence of statemachine_pkg__msg__Command.
typedef struct statemachine_pkg__msg__Command__Sequence
{
  statemachine_pkg__msg__Command * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} statemachine_pkg__msg__Command__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STATEMACHINE_PKG__MSG__DETAIL__COMMAND__STRUCT_H_
