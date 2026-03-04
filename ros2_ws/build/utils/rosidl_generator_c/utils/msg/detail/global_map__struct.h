// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from utils:msg/GlobalMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/global_map.h"


#ifndef UTILS__MSG__DETAIL__GLOBAL_MAP__STRUCT_H_
#define UTILS__MSG__DETAIL__GLOBAL_MAP__STRUCT_H_

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
// Member 'map_type'
// Member 'frame_id'
// Member 'storage_path'
#include "rosidl_runtime_c/string.h"
// Member 'occupied_ix'
// Member 'occupied_iy'
// Member 'occupied_iz'
// Member 'free_ix'
// Member 'free_iy'
// Member 'free_iz'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'frontier_goal'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/GlobalMap in the package utils.
typedef struct utils__msg__GlobalMap
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String map_type;
  rosidl_runtime_c__String frame_id;
  float resolution;
  uint32_t occupied_voxels;
  uint32_t free_voxels;
  uint32_t unknown_voxels;
  float explored_volume_m3;
  rosidl_runtime_c__String storage_path;
  bool valid;
  rosidl_runtime_c__int32__Sequence occupied_ix;
  rosidl_runtime_c__int32__Sequence occupied_iy;
  rosidl_runtime_c__int32__Sequence occupied_iz;
  rosidl_runtime_c__int32__Sequence free_ix;
  rosidl_runtime_c__int32__Sequence free_iy;
  rosidl_runtime_c__int32__Sequence free_iz;
  geometry_msgs__msg__Point frontier_goal;
  bool frontier_goal_valid;
} utils__msg__GlobalMap;

// Struct for a sequence of utils__msg__GlobalMap.
typedef struct utils__msg__GlobalMap__Sequence
{
  utils__msg__GlobalMap * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} utils__msg__GlobalMap__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UTILS__MSG__DETAIL__GLOBAL_MAP__STRUCT_H_
