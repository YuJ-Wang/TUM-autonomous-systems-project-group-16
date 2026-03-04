// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/lantern_pose_array.h"


#ifndef UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__STRUCT_H_
#define UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'lanterns'
#include "utils/msg/detail/lantern_pose__struct.h"

/// Struct defined in msg/LanternPoseArray in the package utils.
typedef struct utils__msg__LanternPoseArray
{
  std_msgs__msg__Header header;
  utils__msg__LanternPose__Sequence lanterns;
  uint32_t confirmed_count;
} utils__msg__LanternPoseArray;

// Struct for a sequence of utils__msg__LanternPoseArray.
typedef struct utils__msg__LanternPoseArray__Sequence
{
  utils__msg__LanternPoseArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__msg__LanternPoseArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UTILS__MSG__DETAIL__LANTERN_POSE_ARRAY__STRUCT_H_
