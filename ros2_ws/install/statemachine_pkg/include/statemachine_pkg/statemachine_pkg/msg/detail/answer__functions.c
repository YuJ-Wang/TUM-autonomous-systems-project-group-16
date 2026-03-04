// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from statemachine_pkg:msg/Answer.idl
// generated code does not contain a copyright notice
#include "statemachine_pkg/msg/detail/answer__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `node_name`
// Member `info`
#include "rosidl_runtime_c/string_functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
statemachine_pkg__msg__Answer__init(statemachine_pkg__msg__Answer * msg)
{
  if (!msg) {
    return false;
  }
  // node_name
  if (!rosidl_runtime_c__String__init(&msg->node_name)) {
    statemachine_pkg__msg__Answer__fini(msg);
    return false;
  }
  // state
  // info
  if (!rosidl_runtime_c__String__init(&msg->info)) {
    statemachine_pkg__msg__Answer__fini(msg);
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    statemachine_pkg__msg__Answer__fini(msg);
    return false;
  }
  return true;
}

void
statemachine_pkg__msg__Answer__fini(statemachine_pkg__msg__Answer * msg)
{
  if (!msg) {
    return;
  }
  // node_name
  rosidl_runtime_c__String__fini(&msg->node_name);
  // state
  // info
  rosidl_runtime_c__String__fini(&msg->info);
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
}

bool
statemachine_pkg__msg__Answer__are_equal(const statemachine_pkg__msg__Answer * lhs, const statemachine_pkg__msg__Answer * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // node_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->node_name), &(rhs->node_name)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // info
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->timestamp), &(rhs->timestamp)))
  {
    return false;
  }
  return true;
}

bool
statemachine_pkg__msg__Answer__copy(
  const statemachine_pkg__msg__Answer * input,
  statemachine_pkg__msg__Answer * output)
{
  if (!input || !output) {
    return false;
  }
  // node_name
  if (!rosidl_runtime_c__String__copy(
      &(input->node_name), &(output->node_name)))
  {
    return false;
  }
  // state
  output->state = input->state;
  // info
  if (!rosidl_runtime_c__String__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->timestamp), &(output->timestamp)))
  {
    return false;
  }
  return true;
}

statemachine_pkg__msg__Answer *
statemachine_pkg__msg__Answer__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statemachine_pkg__msg__Answer * msg = (statemachine_pkg__msg__Answer *)allocator.allocate(sizeof(statemachine_pkg__msg__Answer), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(statemachine_pkg__msg__Answer));
  bool success = statemachine_pkg__msg__Answer__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
statemachine_pkg__msg__Answer__destroy(statemachine_pkg__msg__Answer * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    statemachine_pkg__msg__Answer__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
statemachine_pkg__msg__Answer__Sequence__init(statemachine_pkg__msg__Answer__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statemachine_pkg__msg__Answer * data = NULL;

  if (size) {
    data = (statemachine_pkg__msg__Answer *)allocator.zero_allocate(size, sizeof(statemachine_pkg__msg__Answer), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = statemachine_pkg__msg__Answer__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        statemachine_pkg__msg__Answer__fini(&data[i - 1]);
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
statemachine_pkg__msg__Answer__Sequence__fini(statemachine_pkg__msg__Answer__Sequence * array)
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
      statemachine_pkg__msg__Answer__fini(&array->data[i]);
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

statemachine_pkg__msg__Answer__Sequence *
statemachine_pkg__msg__Answer__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statemachine_pkg__msg__Answer__Sequence * array = (statemachine_pkg__msg__Answer__Sequence *)allocator.allocate(sizeof(statemachine_pkg__msg__Answer__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = statemachine_pkg__msg__Answer__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
statemachine_pkg__msg__Answer__Sequence__destroy(statemachine_pkg__msg__Answer__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    statemachine_pkg__msg__Answer__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
statemachine_pkg__msg__Answer__Sequence__are_equal(const statemachine_pkg__msg__Answer__Sequence * lhs, const statemachine_pkg__msg__Answer__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!statemachine_pkg__msg__Answer__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
statemachine_pkg__msg__Answer__Sequence__copy(
  const statemachine_pkg__msg__Answer__Sequence * input,
  statemachine_pkg__msg__Answer__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(statemachine_pkg__msg__Answer);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    statemachine_pkg__msg__Answer * data =
      (statemachine_pkg__msg__Answer *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!statemachine_pkg__msg__Answer__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          statemachine_pkg__msg__Answer__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!statemachine_pkg__msg__Answer__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
