// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from statemachine_pkg:msg/Command.idl
// generated code does not contain a copyright notice
#include "statemachine_pkg/msg/detail/command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `target`
#include "rosidl_runtime_c/string_functions.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `target_pos`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
statemachine_pkg__msg__Command__init(statemachine_pkg__msg__Command * msg)
{
  if (!msg) {
    return false;
  }
  // target
  if (!rosidl_runtime_c__String__init(&msg->target)) {
    statemachine_pkg__msg__Command__fini(msg);
    return false;
  }
  // command
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    statemachine_pkg__msg__Command__fini(msg);
    return false;
  }
  // has_target
  // target_pos
  if (!geometry_msgs__msg__Point__init(&msg->target_pos)) {
    statemachine_pkg__msg__Command__fini(msg);
    return false;
  }
  return true;
}

void
statemachine_pkg__msg__Command__fini(statemachine_pkg__msg__Command * msg)
{
  if (!msg) {
    return;
  }
  // target
  rosidl_runtime_c__String__fini(&msg->target);
  // command
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // has_target
  // target_pos
  geometry_msgs__msg__Point__fini(&msg->target_pos);
}

bool
statemachine_pkg__msg__Command__are_equal(const statemachine_pkg__msg__Command * lhs, const statemachine_pkg__msg__Command * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // target
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->target), &(rhs->target)))
  {
    return false;
  }
  // command
  if (lhs->command != rhs->command) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // has_target
  if (lhs->has_target != rhs->has_target) {
    return false;
  }
  // target_pos
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->target_pos), &(rhs->target_pos)))
  {
    return false;
  }
  return true;
}

bool
statemachine_pkg__msg__Command__copy(
  const statemachine_pkg__msg__Command * input,
  statemachine_pkg__msg__Command * output)
{
  if (!input || !output) {
    return false;
  }
  // target
  if (!rosidl_runtime_c__String__copy(
      &(input->target), &(output->target)))
  {
    return false;
  }
  // command
  output->command = input->command;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // has_target
  output->has_target = input->has_target;
  // target_pos
  if (!geometry_msgs__msg__Point__copy(
      &(input->target_pos), &(output->target_pos)))
  {
    return false;
  }
  return true;
}

statemachine_pkg__msg__Command *
statemachine_pkg__msg__Command__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statemachine_pkg__msg__Command * msg = (statemachine_pkg__msg__Command *)allocator.allocate(sizeof(statemachine_pkg__msg__Command), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(statemachine_pkg__msg__Command));
  bool success = statemachine_pkg__msg__Command__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
statemachine_pkg__msg__Command__destroy(statemachine_pkg__msg__Command * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    statemachine_pkg__msg__Command__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
statemachine_pkg__msg__Command__Sequence__init(statemachine_pkg__msg__Command__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statemachine_pkg__msg__Command * data = NULL;

  if (size) {
    data = (statemachine_pkg__msg__Command *)allocator.zero_allocate(size, sizeof(statemachine_pkg__msg__Command), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = statemachine_pkg__msg__Command__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        statemachine_pkg__msg__Command__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
statemachine_pkg__msg__Command__Sequence__fini(statemachine_pkg__msg__Command__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      statemachine_pkg__msg__Command__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

statemachine_pkg__msg__Command__Sequence *
statemachine_pkg__msg__Command__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statemachine_pkg__msg__Command__Sequence * array = (statemachine_pkg__msg__Command__Sequence *)allocator.allocate(sizeof(statemachine_pkg__msg__Command__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = statemachine_pkg__msg__Command__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
statemachine_pkg__msg__Command__Sequence__destroy(statemachine_pkg__msg__Command__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    statemachine_pkg__msg__Command__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
statemachine_pkg__msg__Command__Sequence__are_equal(const statemachine_pkg__msg__Command__Sequence * lhs, const statemachine_pkg__msg__Command__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!statemachine_pkg__msg__Command__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
statemachine_pkg__msg__Command__Sequence__copy(
  const statemachine_pkg__msg__Command__Sequence * input,
  statemachine_pkg__msg__Command__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(statemachine_pkg__msg__Command);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    statemachine_pkg__msg__Command * data =
      (statemachine_pkg__msg__Command *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!statemachine_pkg__msg__Command__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          statemachine_pkg__msg__Command__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!statemachine_pkg__msg__Command__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
