// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from utils:srv/SaveMap.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "utils/srv/detail/save_map__rosidl_typesupport_introspection_c.h"
#include "utils/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "utils/srv/detail/save_map__functions.h"
#include "utils/srv/detail/save_map__struct.h"


// Include directives for member types
// Member `file_path`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  utils__srv__SaveMap_Request__init(message_memory);
}

void utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_fini_function(void * message_memory)
{
  utils__srv__SaveMap_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_member_array[1] = {
  {
    "file_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__srv__SaveMap_Request, file_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_members = {
  "utils__srv",  // message namespace
  "SaveMap_Request",  // message name
  1,  // number of fields
  sizeof(utils__srv__SaveMap_Request),
  false,  // has_any_key_member_
  utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_member_array,  // message members
  utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_type_support_handle = {
  0,
  &utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_members,
  get_message_typesupport_handle_function,
  &utils__srv__SaveMap_Request__get_type_hash,
  &utils__srv__SaveMap_Request__get_type_description,
  &utils__srv__SaveMap_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_utils
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Request)() {
  if (!utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_type_support_handle.typesupport_identifier) {
    utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "utils/srv/detail/save_map__rosidl_typesupport_introspection_c.h"
// already included above
// #include "utils/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "utils/srv/detail/save_map__functions.h"
// already included above
// #include "utils/srv/detail/save_map__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  utils__srv__SaveMap_Response__init(message_memory);
}

void utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_fini_function(void * message_memory)
{
  utils__srv__SaveMap_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__srv__SaveMap_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__srv__SaveMap_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_members = {
  "utils__srv",  // message namespace
  "SaveMap_Response",  // message name
  2,  // number of fields
  sizeof(utils__srv__SaveMap_Response),
  false,  // has_any_key_member_
  utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_member_array,  // message members
  utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle = {
  0,
  &utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_members,
  get_message_typesupport_handle_function,
  &utils__srv__SaveMap_Response__get_type_hash,
  &utils__srv__SaveMap_Response__get_type_description,
  &utils__srv__SaveMap_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_utils
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Response)() {
  if (!utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle.typesupport_identifier) {
    utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "utils/srv/detail/save_map__rosidl_typesupport_introspection_c.h"
// already included above
// #include "utils/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "utils/srv/detail/save_map__functions.h"
// already included above
// #include "utils/srv/detail/save_map__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "utils/srv/save_map.h"
// Member `request`
// Member `response`
// already included above
// #include "utils/srv/detail/save_map__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  utils__srv__SaveMap_Event__init(message_memory);
}

void utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_fini_function(void * message_memory)
{
  utils__srv__SaveMap_Event__fini(message_memory);
}

size_t utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__size_function__SaveMap_Event__request(
  const void * untyped_member)
{
  const utils__srv__SaveMap_Request__Sequence * member =
    (const utils__srv__SaveMap_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_const_function__SaveMap_Event__request(
  const void * untyped_member, size_t index)
{
  const utils__srv__SaveMap_Request__Sequence * member =
    (const utils__srv__SaveMap_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_function__SaveMap_Event__request(
  void * untyped_member, size_t index)
{
  utils__srv__SaveMap_Request__Sequence * member =
    (utils__srv__SaveMap_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__fetch_function__SaveMap_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const utils__srv__SaveMap_Request * item =
    ((const utils__srv__SaveMap_Request *)
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_const_function__SaveMap_Event__request(untyped_member, index));
  utils__srv__SaveMap_Request * value =
    (utils__srv__SaveMap_Request *)(untyped_value);
  *value = *item;
}

void utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__assign_function__SaveMap_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  utils__srv__SaveMap_Request * item =
    ((utils__srv__SaveMap_Request *)
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_function__SaveMap_Event__request(untyped_member, index));
  const utils__srv__SaveMap_Request * value =
    (const utils__srv__SaveMap_Request *)(untyped_value);
  *item = *value;
}

bool utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__resize_function__SaveMap_Event__request(
  void * untyped_member, size_t size)
{
  utils__srv__SaveMap_Request__Sequence * member =
    (utils__srv__SaveMap_Request__Sequence *)(untyped_member);
  utils__srv__SaveMap_Request__Sequence__fini(member);
  return utils__srv__SaveMap_Request__Sequence__init(member, size);
}

size_t utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__size_function__SaveMap_Event__response(
  const void * untyped_member)
{
  const utils__srv__SaveMap_Response__Sequence * member =
    (const utils__srv__SaveMap_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_const_function__SaveMap_Event__response(
  const void * untyped_member, size_t index)
{
  const utils__srv__SaveMap_Response__Sequence * member =
    (const utils__srv__SaveMap_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_function__SaveMap_Event__response(
  void * untyped_member, size_t index)
{
  utils__srv__SaveMap_Response__Sequence * member =
    (utils__srv__SaveMap_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__fetch_function__SaveMap_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const utils__srv__SaveMap_Response * item =
    ((const utils__srv__SaveMap_Response *)
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_const_function__SaveMap_Event__response(untyped_member, index));
  utils__srv__SaveMap_Response * value =
    (utils__srv__SaveMap_Response *)(untyped_value);
  *value = *item;
}

void utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__assign_function__SaveMap_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  utils__srv__SaveMap_Response * item =
    ((utils__srv__SaveMap_Response *)
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_function__SaveMap_Event__response(untyped_member, index));
  const utils__srv__SaveMap_Response * value =
    (const utils__srv__SaveMap_Response *)(untyped_value);
  *item = *value;
}

bool utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__resize_function__SaveMap_Event__response(
  void * untyped_member, size_t size)
{
  utils__srv__SaveMap_Response__Sequence * member =
    (utils__srv__SaveMap_Response__Sequence *)(untyped_member);
  utils__srv__SaveMap_Response__Sequence__fini(member);
  return utils__srv__SaveMap_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(utils__srv__SaveMap_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(utils__srv__SaveMap_Event, request),  // bytes offset in struct
    NULL,  // default value
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__size_function__SaveMap_Event__request,  // size() function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_const_function__SaveMap_Event__request,  // get_const(index) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_function__SaveMap_Event__request,  // get(index) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__fetch_function__SaveMap_Event__request,  // fetch(index, &value) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__assign_function__SaveMap_Event__request,  // assign(index, value) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__resize_function__SaveMap_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(utils__srv__SaveMap_Event, response),  // bytes offset in struct
    NULL,  // default value
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__size_function__SaveMap_Event__response,  // size() function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_const_function__SaveMap_Event__response,  // get_const(index) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__get_function__SaveMap_Event__response,  // get(index) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__fetch_function__SaveMap_Event__response,  // fetch(index, &value) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__assign_function__SaveMap_Event__response,  // assign(index, value) function pointer
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__resize_function__SaveMap_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_members = {
  "utils__srv",  // message namespace
  "SaveMap_Event",  // message name
  3,  // number of fields
  sizeof(utils__srv__SaveMap_Event),
  false,  // has_any_key_member_
  utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_member_array,  // message members
  utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_type_support_handle = {
  0,
  &utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_members,
  get_message_typesupport_handle_function,
  &utils__srv__SaveMap_Event__get_type_hash,
  &utils__srv__SaveMap_Event__get_type_description,
  &utils__srv__SaveMap_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_utils
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Event)() {
  utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Request)();
  utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Response)();
  if (!utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_type_support_handle.typesupport_identifier) {
    utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "utils/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "utils/srv/detail/save_map__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_members = {
  "utils__srv",  // service namespace
  "SaveMap",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_Request_message_type_support_handle,
  NULL,  // response message
  // utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle
  NULL  // event_message
  // utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle
};


static rosidl_service_type_support_t utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_type_support_handle = {
  0,
  &utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_members,
  get_service_typesupport_handle_function,
  &utils__srv__SaveMap_Request__rosidl_typesupport_introspection_c__SaveMap_Request_message_type_support_handle,
  &utils__srv__SaveMap_Response__rosidl_typesupport_introspection_c__SaveMap_Response_message_type_support_handle,
  &utils__srv__SaveMap_Event__rosidl_typesupport_introspection_c__SaveMap_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    utils,
    srv,
    SaveMap
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    utils,
    srv,
    SaveMap
  ),
  &utils__srv__SaveMap__get_type_hash,
  &utils__srv__SaveMap__get_type_description,
  &utils__srv__SaveMap__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_utils
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap)(void) {
  if (!utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_type_support_handle.typesupport_identifier) {
    utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SaveMap_Event)()->data;
  }

  return &utils__srv__detail__save_map__rosidl_typesupport_introspection_c__SaveMap_service_type_support_handle;
}
