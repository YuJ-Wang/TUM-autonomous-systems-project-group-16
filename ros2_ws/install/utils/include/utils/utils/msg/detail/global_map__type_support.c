// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from utils:msg/GlobalMap.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "utils/msg/detail/global_map__rosidl_typesupport_introspection_c.h"
#include "utils/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "utils/msg/detail/global_map__functions.h"
#include "utils/msg/detail/global_map__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `map_type`
// Member `frame_id`
// Member `storage_path`
#include "rosidl_runtime_c/string_functions.h"
// Member `occupied_ix`
// Member `occupied_iy`
// Member `occupied_iz`
// Member `free_ix`
// Member `free_iy`
// Member `free_iz`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `frontier_goal`
#include "geometry_msgs/msg/point.h"
// Member `frontier_goal`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  utils__msg__GlobalMap__init(message_memory);
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_fini_function(void * message_memory)
{
  utils__msg__GlobalMap__fini(message_memory);
}

size_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__occupied_ix(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_ix(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_ix(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__occupied_ix(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_ix(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__occupied_ix(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_ix(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__occupied_ix(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__occupied_iy(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_iy(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_iy(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__occupied_iy(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_iy(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__occupied_iy(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_iy(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__occupied_iy(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__occupied_iz(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_iz(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_iz(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__occupied_iz(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_iz(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__occupied_iz(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_iz(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__occupied_iz(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__free_ix(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_ix(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_ix(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__free_ix(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_ix(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__free_ix(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_ix(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__free_ix(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__free_iy(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_iy(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_iy(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__free_iy(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_iy(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__free_iy(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_iy(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__free_iy(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__free_iz(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_iz(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_iz(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__free_iz(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_iz(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__free_iz(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_iz(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__free_iz(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_member_array[18] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, map_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "frame_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "resolution",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, resolution),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "occupied_voxels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, occupied_voxels),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "free_voxels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, free_voxels),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "unknown_voxels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, unknown_voxels),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "explored_volume_m3",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, explored_volume_m3),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "storage_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, storage_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "occupied_ix",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, occupied_ix),  // bytes offset in struct
    NULL,  // default value
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__occupied_ix,  // size() function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_ix,  // get_const(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_ix,  // get(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__occupied_ix,  // fetch(index, &value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__occupied_ix,  // assign(index, value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__occupied_ix  // resize(index) function pointer
  },
  {
    "occupied_iy",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, occupied_iy),  // bytes offset in struct
    NULL,  // default value
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__occupied_iy,  // size() function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_iy,  // get_const(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_iy,  // get(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__occupied_iy,  // fetch(index, &value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__occupied_iy,  // assign(index, value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__occupied_iy  // resize(index) function pointer
  },
  {
    "occupied_iz",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, occupied_iz),  // bytes offset in struct
    NULL,  // default value
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__occupied_iz,  // size() function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__occupied_iz,  // get_const(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__occupied_iz,  // get(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__occupied_iz,  // fetch(index, &value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__occupied_iz,  // assign(index, value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__occupied_iz  // resize(index) function pointer
  },
  {
    "free_ix",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, free_ix),  // bytes offset in struct
    NULL,  // default value
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__free_ix,  // size() function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_ix,  // get_const(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_ix,  // get(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__free_ix,  // fetch(index, &value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__free_ix,  // assign(index, value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__free_ix  // resize(index) function pointer
  },
  {
    "free_iy",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, free_iy),  // bytes offset in struct
    NULL,  // default value
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__free_iy,  // size() function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_iy,  // get_const(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_iy,  // get(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__free_iy,  // fetch(index, &value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__free_iy,  // assign(index, value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__free_iy  // resize(index) function pointer
  },
  {
    "free_iz",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, free_iz),  // bytes offset in struct
    NULL,  // default value
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__size_function__GlobalMap__free_iz,  // size() function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_const_function__GlobalMap__free_iz,  // get_const(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__get_function__GlobalMap__free_iz,  // get(index) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__fetch_function__GlobalMap__free_iz,  // fetch(index, &value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__assign_function__GlobalMap__free_iz,  // assign(index, value) function pointer
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__resize_function__GlobalMap__free_iz  // resize(index) function pointer
  },
  {
    "frontier_goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, frontier_goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "frontier_goal_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__GlobalMap, frontier_goal_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_members = {
  "utils__msg",  // message namespace
  "GlobalMap",  // message name
  18,  // number of fields
  sizeof(utils__msg__GlobalMap),
  false,  // has_any_key_member_
  utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_member_array,  // message members
  utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_init_function,  // function to initialize message memory (memory has to be allocated)
  utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_type_support_handle = {
  0,
  &utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_members,
  get_message_typesupport_handle_function,
  &utils__msg__GlobalMap__get_type_hash,
  &utils__msg__GlobalMap__get_type_description,
  &utils__msg__GlobalMap__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_utils
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, msg, GlobalMap)() {
  utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_member_array[16].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_type_support_handle.typesupport_identifier) {
    utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &utils__msg__GlobalMap__rosidl_typesupport_introspection_c__GlobalMap_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
