// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice

#include "statemachine_pkg/msg/detail/answer__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_statemachine_pkg
const rosidl_type_hash_t *
statemachine_pkg__msg__Answer__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3c, 0xfa, 0xc8, 0xb3, 0x1d, 0x0c, 0x68, 0x20,
      0xa4, 0x4f, 0xb4, 0xfd, 0x2a, 0x77, 0x87, 0x51,
      0xc2, 0xa4, 0x94, 0xad, 0x67, 0x71, 0xf2, 0xc0,
      0x8d, 0x86, 0x52, 0x26, 0xc1, 0x24, 0xda, 0x1b,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
#endif

static char statemachine_pkg__msg__Answer__TYPE_NAME[] = "statemachine_pkg/msg/Answer";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char statemachine_pkg__msg__Answer__FIELD_NAME__node_name[] = "node_name";
static char statemachine_pkg__msg__Answer__FIELD_NAME__state[] = "state";
static char statemachine_pkg__msg__Answer__FIELD_NAME__info[] = "info";
static char statemachine_pkg__msg__Answer__FIELD_NAME__timestamp[] = "timestamp";

static rosidl_runtime_c__type_description__Field statemachine_pkg__msg__Answer__FIELDS[] = {
  {
    {statemachine_pkg__msg__Answer__FIELD_NAME__node_name, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {statemachine_pkg__msg__Answer__FIELD_NAME__state, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {statemachine_pkg__msg__Answer__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {statemachine_pkg__msg__Answer__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription statemachine_pkg__msg__Answer__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
statemachine_pkg__msg__Answer__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {statemachine_pkg__msg__Answer__TYPE_NAME, 27, 27},
      {statemachine_pkg__msg__Answer__FIELDS, 4, 4},
    },
    {statemachine_pkg__msg__Answer__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string node_name\n"
  "uint8 state\n"
  "string info\n"
  "builtin_interfaces/Time timestamp";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
statemachine_pkg__msg__Answer__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {statemachine_pkg__msg__Answer__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 74, 74},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
statemachine_pkg__msg__Answer__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *statemachine_pkg__msg__Answer__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
