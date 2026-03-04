// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from utils:msg/LanternPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose.h"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE__STRUCT_H_
#define UTILS__MSG__DETAIL__LANTERN_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'source_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/LanternPose in the package utils.
typedef struct utils__msg__LanternPose
{
  builtin_interfaces__msg__Time stamp;
  uint32_t id;
  geometry_msgs__msg__Pose pose;
  float confidence;
  bool confirmed;
  rosidl_runtime_c__String source_frame;
} utils__msg__LanternPose;

// Struct for a sequence of utils__msg__LanternPose.
typedef struct utils__msg__LanternPose__Sequence
{
  utils__msg__LanternPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__msg__LanternPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE__STRUCT_H_
