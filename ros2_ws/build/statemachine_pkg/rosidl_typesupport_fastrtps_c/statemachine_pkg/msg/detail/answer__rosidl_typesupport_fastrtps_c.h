// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice
#ifndef STATEMACHINE_PKG__MSG__DETAIL__ANSWER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define STATEMACHINE_PKG__MSG__DETAIL__ANSWER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "statemachine_pkg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "statemachine_pkg/msg/detail/answer__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
bool cdr_serialize_statemachine_pkg__msg__Answer(
  const statemachine_pkg__msg__Answer * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
bool cdr_deserialize_statemachine_pkg__msg__Answer(
  eprosima::fastcdr::Cdr &,
  statemachine_pkg__msg__Answer * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
size_t get_serialized_size_statemachine_pkg__msg__Answer(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
size_t max_serialized_size_statemachine_pkg__msg__Answer(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
bool cdr_serialize_key_statemachine_pkg__msg__Answer(
  const statemachine_pkg__msg__Answer * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
size_t get_serialized_size_key_statemachine_pkg__msg__Answer(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
size_t max_serialized_size_key_statemachine_pkg__msg__Answer(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_statemachine_pkg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, statemachine_pkg, msg, Answer)();

#ifdef __cplusplus
}
#endif

#endif  // STATEMACHINE_PKG__MSG__DETAIL__ANSWER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
