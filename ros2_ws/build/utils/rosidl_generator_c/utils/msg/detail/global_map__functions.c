// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from utils:msg/GlobalMap.idl
// generated code does not contain a copyright notice
#include "utils/msg/detail/global_map__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `map_type`
// Member `frame_id`
// Member `storage_path`
#include "rosidl_runtime_c/string_functions.h"
// Member `occupied_ix`
// Member `occupied_iy`
// Member `occupied_iz`
// Member `free_ix`
// Member `free_iy`
// Member `free_iz`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `frontier_goal`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
utils__msg__GlobalMap__init(utils__msg__GlobalMap * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // map_type
  if (!rosidl_runtime_c__String__init(&msg->map_type)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // frame_id
  if (!rosidl_runtime_c__String__init(&msg->frame_id)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // resolution
  // occupied_voxels
  // free_voxels
  // unknown_voxels
  // explored_volume_m3
  // storage_path
  if (!rosidl_runtime_c__String__init(&msg->storage_path)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // valid
  // occupied_ix
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->occupied_ix, 0)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // occupied_iy
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->occupied_iy, 0)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // occupied_iz
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->occupied_iz, 0)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // free_ix
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->free_ix, 0)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // free_iy
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->free_iy, 0)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // free_iz
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->free_iz, 0)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // frontier_goal
  if (!geometry_msgs__msg__Point__init(&msg->frontier_goal)) {
    utils__msg__GlobalMap__fini(msg);
    return false;
  }
  // frontier_goal_valid
  return true;
}

void
utils__msg__GlobalMap__fini(utils__msg__GlobalMap * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // map_type
  rosidl_runtime_c__String__fini(&msg->map_type);
  // frame_id
  rosidl_runtime_c__String__fini(&msg->frame_id);
  // resolution
  // occupied_voxels
  // free_voxels
  // unknown_voxels
  // explored_volume_m3
  // storage_path
  rosidl_runtime_c__String__fini(&msg->storage_path);
  // valid
  // occupied_ix
  rosidl_runtime_c__int32__Sequence__fini(&msg->occupied_ix);
  // occupied_iy
  rosidl_runtime_c__int32__Sequence__fini(&msg->occupied_iy);
  // occupied_iz
  rosidl_runtime_c__int32__Sequence__fini(&msg->occupied_iz);
  // free_ix
  rosidl_runtime_c__int32__Sequence__fini(&msg->free_ix);
  // free_iy
  rosidl_runtime_c__int32__Sequence__fini(&msg->free_iy);
  // free_iz
  rosidl_runtime_c__int32__Sequence__fini(&msg->free_iz);
  // frontier_goal
  geometry_msgs__msg__Point__fini(&msg->frontier_goal);
  // frontier_goal_valid
}

bool
utils__msg__GlobalMap__are_equal(const utils__msg__GlobalMap * lhs, const utils__msg__GlobalMap * rhs)
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
  // map_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_type), &(rhs->map_type)))
  {
    return false;
  }
  // frame_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->frame_id), &(rhs->frame_id)))
  {
    return false;
  }
  // resolution
  if (lhs->resolution != rhs->resolution) {
    return false;
  }
  // occupied_voxels
  if (lhs->occupied_voxels != rhs->occupied_voxels) {
    return false;
  }
  // free_voxels
  if (lhs->free_voxels != rhs->free_voxels) {
    return false;
  }
  // unknown_voxels
  if (lhs->unknown_voxels != rhs->unknown_voxels) {
    return false;
  }
  // explored_volume_m3
  if (lhs->explored_volume_m3 != rhs->explored_volume_m3) {
    return false;
  }
  // storage_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->storage_path), &(rhs->storage_path)))
  {
    return false;
  }
  // valid
  if (lhs->valid != rhs->valid) {
    return false;
  }
  // occupied_ix
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->occupied_ix), &(rhs->occupied_ix)))
  {
    return false;
  }
  // occupied_iy
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->occupied_iy), &(rhs->occupied_iy)))
  {
    return false;
  }
  // occupied_iz
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->occupied_iz), &(rhs->occupied_iz)))
  {
    return false;
  }
  // free_ix
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->free_ix), &(rhs->free_ix)))
  {
    return false;
  }
  // free_iy
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->free_iy), &(rhs->free_iy)))
  {
    return false;
  }
  // free_iz
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->free_iz), &(rhs->free_iz)))
  {
    return false;
  }
  // frontier_goal
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->frontier_goal), &(rhs->frontier_goal)))
  {
    return false;
  }
  // frontier_goal_valid
  if (lhs->frontier_goal_valid != rhs->frontier_goal_valid) {
    return false;
  }
  return true;
}

bool
utils__msg__GlobalMap__copy(
  const utils__msg__GlobalMap * input,
  utils__msg__GlobalMap * output)
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
  // map_type
  if (!rosidl_runtime_c__String__copy(
      &(input->map_type), &(output->map_type)))
  {
    return false;
  }
  // frame_id
  if (!rosidl_runtime_c__String__copy(
      &(input->frame_id), &(output->frame_id)))
  {
    return false;
  }
  // resolution
  output->resolution = input->resolution;
  // occupied_voxels
  output->occupied_voxels = input->occupied_voxels;
  // free_voxels
  output->free_voxels = input->free_voxels;
  // unknown_voxels
  output->unknown_voxels = input->unknown_voxels;
  // explored_volume_m3
  output->explored_volume_m3 = input->explored_volume_m3;
  // storage_path
  if (!rosidl_runtime_c__String__copy(
      &(input->storage_path), &(output->storage_path)))
  {
    return false;
  }
  // valid
  output->valid = input->valid;
  // occupied_ix
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->occupied_ix), &(output->occupied_ix)))
  {
    return false;
  }
  // occupied_iy
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->occupied_iy), &(output->occupied_iy)))
  {
    return false;
  }
  // occupied_iz
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->occupied_iz), &(output->occupied_iz)))
  {
    return false;
  }
  // free_ix
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->free_ix), &(output->free_ix)))
  {
    return false;
  }
  // free_iy
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->free_iy), &(output->free_iy)))
  {
    return false;
  }
  // free_iz
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->free_iz), &(output->free_iz)))
  {
    return false;
  }
  // frontier_goal
  if (!geometry_msgs__msg__Point__copy(
      &(input->frontier_goal), &(output->frontier_goal)))
  {
    return false;
  }
  // frontier_goal_valid
  output->frontier_goal_valid = input->frontier_goal_valid;
  return true;
}

utils__msg__GlobalMap *
utils__msg__GlobalMap__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__GlobalMap * msg = (utils__msg__GlobalMap *)allocator.allocate(sizeof(utils__msg__GlobalMap), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(utils__msg__GlobalMap));
  bool success = utils__msg__GlobalMap__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
utils__msg__GlobalMap__destroy(utils__msg__GlobalMap * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    utils__msg__GlobalMap__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
utils__msg__GlobalMap__Sequence__init(utils__msg__GlobalMap__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__GlobalMap * data = NULL;

  if (size) {
    data = (utils__msg__GlobalMap *)allocator.zero_allocate(size, sizeof(utils__msg__GlobalMap), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = utils__msg__GlobalMap__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        utils__msg__GlobalMap__fini(&data[i - 1]);
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
utils__msg__GlobalMap__Sequence__fini(utils__msg__GlobalMap__Sequence * array)
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
      utils__msg__GlobalMap__fini(&array->data[i]);
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

utils__msg__GlobalMap__Sequence *
utils__msg__GlobalMap__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  utils__msg__GlobalMap__Sequence * array = (utils__msg__GlobalMap__Sequence *)allocator.allocate(sizeof(utils__msg__GlobalMap__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = utils__msg__GlobalMap__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
utils__msg__GlobalMap__Sequence__destroy(utils__msg__GlobalMap__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    utils__msg__GlobalMap__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
utils__msg__GlobalMap__Sequence__are_equal(const utils__msg__GlobalMap__Sequence * lhs, const utils__msg__GlobalMap__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!utils__msg__GlobalMap__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
utils__msg__GlobalMap__Sequence__copy(
  const utils__msg__GlobalMap__Sequence * input,
  utils__msg__GlobalMap__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(utils__msg__GlobalMap);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    utils__msg__GlobalMap * data =
      (utils__msg__GlobalMap *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!utils__msg__GlobalMap__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          utils__msg__GlobalMap__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!utils__msg__GlobalMap__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
