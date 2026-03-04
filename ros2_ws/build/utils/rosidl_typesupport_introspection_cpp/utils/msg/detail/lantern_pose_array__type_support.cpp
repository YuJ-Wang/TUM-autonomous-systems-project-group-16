// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "utils/msg/detail/lantern_pose_array__functions.h"
#include "utils/msg/detail/lantern_pose_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace utils
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void LanternPoseArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) utils::msg::LanternPoseArray(_init);
}

void LanternPoseArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<utils::msg::LanternPoseArray *>(message_memory);
  typed_message->~LanternPoseArray();
}

size_t size_function__LanternPoseArray__lanterns(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<utils::msg::LanternPose> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LanternPoseArray__lanterns(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<utils::msg::LanternPose> *>(untyped_member);
  return &member[index];
}

void * get_function__LanternPoseArray__lanterns(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<utils::msg::LanternPose> *>(untyped_member);
  return &member[index];
}

void fetch_function__LanternPoseArray__lanterns(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const utils::msg::LanternPose *>(
    get_const_function__LanternPoseArray__lanterns(untyped_member, index));
  auto & value = *reinterpret_cast<utils::msg::LanternPose *>(untyped_value);
  value = item;
}

void assign_function__LanternPoseArray__lanterns(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<utils::msg::LanternPose *>(
    get_function__LanternPoseArray__lanterns(untyped_member, index));
  const auto & value = *reinterpret_cast<const utils::msg::LanternPose *>(untyped_value);
  item = value;
}

void resize_function__LanternPoseArray__lanterns(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<utils::msg::LanternPose> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LanternPoseArray_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils::msg::LanternPoseArray, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "lanterns",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<utils::msg::LanternPose>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils::msg::LanternPoseArray, lanterns),  // bytes offset in struct
    nullptr,  // default value
    size_function__LanternPoseArray__lanterns,  // size() function pointer
    get_const_function__LanternPoseArray__lanterns,  // get_const(index) function pointer
    get_function__LanternPoseArray__lanterns,  // get(index) function pointer
    fetch_function__LanternPoseArray__lanterns,  // fetch(index, &value) function pointer
    assign_function__LanternPoseArray__lanterns,  // assign(index, value) function pointer
    resize_function__LanternPoseArray__lanterns  // resize(index) function pointer
  },
  {
    "confirmed_count",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils::msg::LanternPoseArray, confirmed_count),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LanternPoseArray_message_members = {
  "utils::msg",  // message namespace
  "LanternPoseArray",  // message name
  3,  // number of fields
  sizeof(utils::msg::LanternPoseArray),
  false,  // has_any_key_member_
  LanternPoseArray_message_member_array,  // message members
  LanternPoseArray_init_function,  // function to initialize message memory (memory has to be allocated)
  LanternPoseArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LanternPoseArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LanternPoseArray_message_members,
  get_message_typesupport_handle_function,
  &utils__msg__LanternPoseArray__get_type_hash,
  &utils__msg__LanternPoseArray__get_type_description,
  &utils__msg__LanternPoseArray__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace utils


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<utils::msg::LanternPoseArray>()
{
  return &::utils::msg::rosidl_typesupport_introspection_cpp::LanternPoseArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, utils, msg, LanternPoseArray)() {
  return &::utils::msg::rosidl_typesupport_introspection_cpp::LanternPoseArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
