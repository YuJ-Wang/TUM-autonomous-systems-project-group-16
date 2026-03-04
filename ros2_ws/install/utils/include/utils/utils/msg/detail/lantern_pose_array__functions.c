// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from utils:msg/LanternPoseArray.idl
// generated code does not contain a copyright notice
#include "utils/msg/detail/lantern_pose_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `lanterns`
#include "utils/msg/detail/lantern_pose__functions.h"

bool
utils__msg__LanternPoseArray__init(utils__msg__LanternPoseArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    utils__msg__LanternPoseArray__fini(msg);
    return false;
  }
  // lanterns
  if (!utils__msg__LanternPose__Sequence__init(&msg->lanterns, 0)) {
    utils__msg__LanternPoseArray__fini(msg);
    return false;
  }
  // confirmed_count
  return true;
}

void
utils__msg__LanternPoseArray__fini(utils__msg__LanternPoseArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // lanterns
  utils__msg__LanternPose__Sequence__fini(&msg->lanterns);
  // confirmed_count
}

bool
utils__msg__LanternPoseArray__are_equal(const utils__msg__LanternPoseArray * lhs, const utils__msg__LanternPoseArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // lanterns
  if (!utils__msg__LanternPose__Sequence__are_equal(
      &(lhs->lanterns), &(rhs->lanterns)))
  {
    return false;
  }
  // confirmed_count
  if (lhs->confirmed_count != rhs->confirmed_count) {
    return false;
  }
  return true;
}

bool
utils__msg__LanternPoseArray__copy(
  const utils__msg__LanternPoseArray * input,
  utils__msg__LanternPoseArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // lanterns
  if (!utils__msg__LanternPose__Sequence__copy(
      &(input->lanterns), &(output->lanterns)))
  {
    return false;
  }
  // confirmed_count
  output->confirmed_count = input->confirmed_count;
  return true;
}

utils__msg__LanternPoseArray *
utils__msg__LanternPoseArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__LanternPoseArray * msg = (utils__msg__LanternPoseArray *)allocator.allocate(sizeof(utils__msg__LanternPoseArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(utils__msg__LanternPoseArray));
  bool success = utils__msg__LanternPoseArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
utils__msg__LanternPoseArray__destroy(utils__msg__LanternPoseArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    utils__msg__LanternPoseArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
utils__msg__LanternPoseArray__Sequence__init(utils__msg__LanternPoseArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__LanternPoseArray * data = NULL;

  if (size) {
    data = (utils__msg__LanternPoseArray *)allocator.zero_allocate(size, sizeof(utils__msg__LanternPoseArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = utils__msg__LanternPoseArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        utils__msg__LanternPoseArray__fini(&data[i - 1]);
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
utils__msg__LanternPoseArray__Sequence__fini(utils__msg__LanternPoseArray__Sequence * array)
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
      utils__msg__LanternPoseArray__fini(&array->data[i]);
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

utils__msg__LanternPoseArray__Sequence *
utils__msg__LanternPoseArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__LanternPoseArray__Sequence * array = (utils__msg__LanternPoseArray__Sequence *)allocator.allocate(sizeof(utils__msg__LanternPoseArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = utils__msg__LanternPoseArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
utils__msg__LanternPoseArray__Sequence__destroy(utils__msg__LanternPoseArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    utils__msg__LanternPoseArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
utils__msg__LanternPoseArray__Sequence__are_equal(const utils__msg__LanternPoseArray__Sequence * lhs, const utils__msg__LanternPoseArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!utils__msg__LanternPoseArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
utils__msg__LanternPoseArray__Sequence__copy(
  const utils__msg__LanternPoseArray__Sequence * input,
  utils__msg__LanternPoseArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(utils__msg__LanternPoseArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    utils__msg__LanternPoseArray * data =
      (utils__msg__LanternPoseArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!utils__msg__LanternPoseArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          utils__msg__LanternPoseArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!utils__msg__LanternPoseArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
