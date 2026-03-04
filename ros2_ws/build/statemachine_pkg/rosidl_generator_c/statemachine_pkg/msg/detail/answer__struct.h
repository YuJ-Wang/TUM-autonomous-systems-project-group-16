// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statemachine_pkg/msg/answer.h"


#ifndef STATEMACHINE_PKG__MSG__DETAIL__ANSWER__STRUCT_H_
#define STATEMACHINE_PKG__MSG__DETAIL__ANSWER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'node_name'
// Member 'info'
#include "rosidl_runtime_c/string.h"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/Answer in the package statemachine_pkg.
typedef struct statemachine_pkg__msg__Answer
{
  rosidl_runtime_c__String node_name;
  uint8_t state;
  rosidl_runtime_c__String info;
  builtin_interfaces__msg__Time timestamp;
} statemachine_pkg__msg__Answer;

// Struct for a sequence of statemachine_pkg__msg__Answer.
typedef struct statemachine_pkg__msg__Answer__Sequence
{
  statemachine_pkg__msg__Answer * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} statemachine_pkg__msg__Answer__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STATEMACHINE_PKG__MSG__DETAIL__ANSWER__STRUCT_H_
