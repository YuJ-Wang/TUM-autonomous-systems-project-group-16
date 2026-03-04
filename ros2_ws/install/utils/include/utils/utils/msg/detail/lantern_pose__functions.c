// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from utils:msg/LanternPose.idl
// generated code does not contain a copyright notice
#include "utils/msg/detail/lantern_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"
// Member `source_frame`
#include "rosidl_runtime_c/string_functions.h"

bool
utils__msg__LanternPose__init(utils__msg__LanternPose * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    utils__msg__LanternPose__fini(msg);
    return false;
  }
  // id
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    utils__msg__LanternPose__fini(msg);
    return false;
  }
  // confidence
  // confirmed
  // source_frame
  if (!rosidl_runtime_c__String__init(&msg->source_frame)) {
    utils__msg__LanternPose__fini(msg);
    return false;
  }
  return true;
}

void
utils__msg__LanternPose__fini(utils__msg__LanternPose * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // id
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
  // confidence
  // confirmed
  // source_frame
  rosidl_runtime_c__String__fini(&msg->source_frame);
}

bool
utils__msg__LanternPose__are_equal(const utils__msg__LanternPose * lhs, const utils__msg__LanternPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // confirmed
  if (lhs->confirmed != rhs->confirmed) {
    return false;
  }
  // source_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source_frame), &(rhs->source_frame)))
  {
    return false;
  }
  return true;
}

bool
utils__msg__LanternPose__copy(
  const utils__msg__LanternPose * input,
  utils__msg__LanternPose * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // id
  output->id = input->id;
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // confirmed
  output->confirmed = input->confirmed;
  // source_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->source_frame), &(output->source_frame)))
  {
    return false;
  }
  return true;
}

utils__msg__LanternPose *
utils__msg__LanternPose__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__LanternPose * msg = (utils__msg__LanternPose *)allocator.allocate(sizeof(utils__msg__LanternPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(utils__msg__LanternPose));
  bool success = utils__msg__LanternPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
utils__msg__LanternPose__destroy(utils__msg__LanternPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    utils__msg__LanternPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
utils__msg__LanternPose__Sequence__init(utils__msg__LanternPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__LanternPose * data = NULL;

  if (size) {
    data = (utils__msg__LanternPose *)allocator.zero_allocate(size, sizeof(utils__msg__LanternPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = utils__msg__LanternPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        utils__msg__LanternPose__fini(&data[i - 1]);
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
utils__msg__LanternPose__Sequence__fini(utils__msg__LanternPose__Sequence * array)
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
      utils__msg__LanternPose__fini(&array->data[i]);
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

utils__msg__LanternPose__Sequence *
utils__msg__LanternPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__LanternPose__Sequence * array = (utils__msg__LanternPose__Sequence *)allocator.allocate(sizeof(utils__msg__LanternPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = utils__msg__LanternPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
utils__msg__LanternPose__Sequence__destroy(utils__msg__LanternPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    utils__msg__LanternPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
utils__msg__LanternPose__Sequence__are_equal(const utils__msg__LanternPose__Sequence * lhs, const utils__msg__LanternPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!utils__msg__LanternPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
utils__msg__LanternPose__Sequence__copy(
  const utils__msg__LanternPose__Sequence * input,
  utils__msg__LanternPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(utils__msg__LanternPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    utils__msg__LanternPose * data =
      (utils__msg__LanternPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!utils__msg__LanternPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          utils__msg__LanternPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!utils__msg__LanternPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
