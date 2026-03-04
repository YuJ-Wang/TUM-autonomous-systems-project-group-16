// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from utils:srv/SetMissionMode.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "utils/srv/detail/set_mission_mode__struct.h"
#include "utils/srv/detail/set_mission_mode__type_support.h"
#include "utils/srv/detail/set_mission_mode__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace utils
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _SetMissionMode_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetMissionMode_Request_type_support_ids_t;

static const _SetMissionMode_Request_type_support_ids_t _SetMissionMode_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SetMissionMode_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetMissionMode_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetMissionMode_Request_type_support_symbol_names_t _SetMissionMode_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, utils, srv, SetMissionMode_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SetMissionMode_Request)),
  }
};

typedef struct _SetMissionMode_Request_type_support_data_t
{
  void * data[2];
} _SetMissionMode_Request_type_support_data_t;

static _SetMissionMode_Request_type_support_data_t _SetMissionMode_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetMissionMode_Request_message_typesupport_map = {
  2,
  "utils",
  &_SetMissionMode_Request_message_typesupport_ids.typesupport_identifier[0],
  &_SetMissionMode_Request_message_typesupport_symbol_names.symbol_name[0],
  &_SetMissionMode_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetMissionMode_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetMissionMode_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &utils__srv__SetMissionMode_Request__get_type_hash,
  &utils__srv__SetMissionMode_Request__get_type_description,
  &utils__srv__SetMissionMode_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace utils

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, utils, srv, SetMissionMode_Request)() {
  return &::utils::srv::rosidl_typesupport_c::SetMissionMode_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__struct.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__type_support.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace utils
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _SetMissionMode_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetMissionMode_Response_type_support_ids_t;

static const _SetMissionMode_Response_type_support_ids_t _SetMissionMode_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SetMissionMode_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetMissionMode_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetMissionMode_Response_type_support_symbol_names_t _SetMissionMode_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, utils, srv, SetMissionMode_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SetMissionMode_Response)),
  }
};

typedef struct _SetMissionMode_Response_type_support_data_t
{
  void * data[2];
} _SetMissionMode_Response_type_support_data_t;

static _SetMissionMode_Response_type_support_data_t _SetMissionMode_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetMissionMode_Response_message_typesupport_map = {
  2,
  "utils",
  &_SetMissionMode_Response_message_typesupport_ids.typesupport_identifier[0],
  &_SetMissionMode_Response_message_typesupport_symbol_names.symbol_name[0],
  &_SetMissionMode_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetMissionMode_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetMissionMode_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &utils__srv__SetMissionMode_Response__get_type_hash,
  &utils__srv__SetMissionMode_Response__get_type_description,
  &utils__srv__SetMissionMode_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace utils

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, utils, srv, SetMissionMode_Response)() {
  return &::utils::srv::rosidl_typesupport_c::SetMissionMode_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__struct.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__type_support.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace utils
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _SetMissionMode_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetMissionMode_Event_type_support_ids_t;

static const _SetMissionMode_Event_type_support_ids_t _SetMissionMode_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SetMissionMode_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetMissionMode_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetMissionMode_Event_type_support_symbol_names_t _SetMissionMode_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, utils, srv, SetMissionMode_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SetMissionMode_Event)),
  }
};

typedef struct _SetMissionMode_Event_type_support_data_t
{
  void * data[2];
} _SetMissionMode_Event_type_support_data_t;

static _SetMissionMode_Event_type_support_data_t _SetMissionMode_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetMissionMode_Event_message_typesupport_map = {
  2,
  "utils",
  &_SetMissionMode_Event_message_typesupport_ids.typesupport_identifier[0],
  &_SetMissionMode_Event_message_typesupport_symbol_names.symbol_name[0],
  &_SetMissionMode_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetMissionMode_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetMissionMode_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &utils__srv__SetMissionMode_Event__get_type_hash,
  &utils__srv__SetMissionMode_Event__get_type_description,
  &utils__srv__SetMissionMode_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace utils

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, utils, srv, SetMissionMode_Event)() {
  return &::utils::srv::rosidl_typesupport_c::SetMissionMode_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "utils/srv/detail/set_mission_mode__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace utils
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _SetMissionMode_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetMissionMode_type_support_ids_t;

static const _SetMissionMode_type_support_ids_t _SetMissionMode_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SetMissionMode_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetMissionMode_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetMissionMode_type_support_symbol_names_t _SetMissionMode_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, utils, srv, SetMissionMode)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, utils, srv, SetMissionMode)),
  }
};

typedef struct _SetMissionMode_type_support_data_t
{
  void * data[2];
} _SetMissionMode_type_support_data_t;

static _SetMissionMode_type_support_data_t _SetMissionMode_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetMissionMode_service_typesupport_map = {
  2,
  "utils",
  &_SetMissionMode_service_typesupport_ids.typesupport_identifier[0],
  &_SetMissionMode_service_typesupport_symbol_names.symbol_name[0],
  &_SetMissionMode_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t SetMissionMode_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetMissionMode_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &SetMissionMode_Request_message_type_support_handle,
  &SetMissionMode_Response_message_type_support_handle,
  &SetMissionMode_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    utils,
    srv,
    SetMissionMode
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    utils,
    srv,
    SetMissionMode
  ),
  &utils__srv__SetMissionMode__get_type_hash,
  &utils__srv__SetMissionMode__get_type_description,
  &utils__srv__SetMissionMode__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace utils

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, utils, srv, SetMissionMode)() {
  return &::utils::srv::rosidl_typesupport_c::SetMissionMode_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
