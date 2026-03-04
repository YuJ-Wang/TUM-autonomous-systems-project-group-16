// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "utils/msg/detail/lantern_pose_array__rosidl_typesupport_introspection_c.h"
#include "utils/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "utils/msg/detail/lantern_pose_array__functions.h"
#include "utils/msg/detail/lantern_pose_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `lanterns`
#include "utils/msg/lantern_pose.h"
// Member `lanterns`
#include "utils/msg/detail/lantern_pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  utils__msg__LanternPoseArray__init(message_memory);
}

void utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_fini_function(void * message_memory)
{
  utils__msg__LanternPoseArray__fini(message_memory);
}

size_t utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__size_function__LanternPoseArray__lanterns(
  const void * untyped_member)
{
  const utils__msg__LanternPose__Sequence * member =
    (const utils__msg__LanternPose__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__get_const_function__LanternPoseArray__lanterns(
  const void * untyped_member, size_t index)
{
  const utils__msg__LanternPose__Sequence * member =
    (const utils__msg__LanternPose__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__get_function__LanternPoseArray__lanterns(
  void * untyped_member, size_t index)
{
  utils__msg__LanternPose__Sequence * member =
    (utils__msg__LanternPose__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__fetch_function__LanternPoseArray__lanterns(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const utils__msg__LanternPose * item =
    ((const utils__msg__LanternPose *)
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__get_const_function__LanternPoseArray__lanterns(untyped_member, index));
  utils__msg__LanternPose * value =
    (utils__msg__LanternPose *)(untyped_value);
  *value = *item;
}

void utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__assign_function__LanternPoseArray__lanterns(
  void * untyped_member, size_t index, const void * untyped_value)
{
  utils__msg__LanternPose * item =
    ((utils__msg__LanternPose *)
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__get_function__LanternPoseArray__lanterns(untyped_member, index));
  const utils__msg__LanternPose * value =
    (const utils__msg__LanternPose *)(untyped_value);
  *item = *value;
}

bool utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__resize_function__LanternPoseArray__lanterns(
  void * untyped_member, size_t size)
{
  utils__msg__LanternPose__Sequence * member =
    (utils__msg__LanternPose__Sequence *)(untyped_member);
  utils__msg__LanternPose__Sequence__fini(member);
  return utils__msg__LanternPose__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__LanternPoseArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "lanterns",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__LanternPoseArray, lanterns),  // bytes offset in struct
    NULL,  // default value
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__size_function__LanternPoseArray__lanterns,  // size() function pointer
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__get_const_function__LanternPoseArray__lanterns,  // get_const(index) function pointer
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__get_function__LanternPoseArray__lanterns,  // get(index) function pointer
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__fetch_function__LanternPoseArray__lanterns,  // fetch(index, &value) function pointer
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__assign_function__LanternPoseArray__lanterns,  // assign(index, value) function pointer
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__resize_function__LanternPoseArray__lanterns  // resize(index) function pointer
  },
  {
    "confirmed_count",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__msg__LanternPoseArray, confirmed_count),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_members = {
  "utils__msg",  // message namespace
  "LanternPoseArray",  // message name
  3,  // number of fields
  sizeof(utils__msg__LanternPoseArray),
  false,  // has_any_key_member_
  utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_member_array,  // message members
  utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_init_function,  // function to initialize message memory (memory has to be allocated)
  utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_type_support_handle = {
  0,
  &utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_members,
  get_message_typesupport_handle_function,
  &utils__msg__LanternPoseArray__get_type_hash,
  &utils__msg__LanternPoseArray__get_type_description,
  &utils__msg__LanternPoseArray__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_utils
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, msg, LanternPoseArray)() {
  utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, msg, LanternPose)();
  if (!utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_type_support_handle.typesupport_identifier) {
    utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &utils__msg__LanternPoseArray__rosidl_typesupport_introspection_c__LanternPoseArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
