// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from utils:msg/GlobalMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/global_map.hpp"


#ifndef UTILS__MSG__DETAIL__GLOBAL_MAP__BUILDER_HPP_
#define UTILS__MSG__DETAIL__GLOBAL_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "utils/msg/detail/global_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace utils
{

namespace msg
{

namespace builder
{

class Init_GlobalMap_frontier_goal_valid
{
public:
  explicit Init_GlobalMap_frontier_goal_valid(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  ::utils::msg::GlobalMap frontier_goal_valid(::utils::msg::GlobalMap::_frontier_goal_valid_type arg)
  {
    msg_.frontier_goal_valid = std::move(arg);
    return std::move(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_frontier_goal
{
public:
  explicit Init_GlobalMap_frontier_goal(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_frontier_goal_valid frontier_goal(::utils::msg::GlobalMap::_frontier_goal_type arg)
  {
    msg_.frontier_goal = std::move(arg);
    return Init_GlobalMap_frontier_goal_valid(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_free_iz
{
public:
  explicit Init_GlobalMap_free_iz(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_frontier_goal free_iz(::utils::msg::GlobalMap::_free_iz_type arg)
  {
    msg_.free_iz = std::move(arg);
    return Init_GlobalMap_frontier_goal(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_free_iy
{
public:
  explicit Init_GlobalMap_free_iy(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_free_iz free_iy(::utils::msg::GlobalMap::_free_iy_type arg)
  {
    msg_.free_iy = std::move(arg);
    return Init_GlobalMap_free_iz(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_free_ix
{
public:
  explicit Init_GlobalMap_free_ix(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_free_iy free_ix(::utils::msg::GlobalMap::_free_ix_type arg)
  {
    msg_.free_ix = std::move(arg);
    return Init_GlobalMap_free_iy(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_occupied_iz
{
public:
  explicit Init_GlobalMap_occupied_iz(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_free_ix occupied_iz(::utils::msg::GlobalMap::_occupied_iz_type arg)
  {
    msg_.occupied_iz = std::move(arg);
    return Init_GlobalMap_free_ix(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_occupied_iy
{
public:
  explicit Init_GlobalMap_occupied_iy(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_occupied_iz occupied_iy(::utils::msg::GlobalMap::_occupied_iy_type arg)
  {
    msg_.occupied_iy = std::move(arg);
    return Init_GlobalMap_occupied_iz(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_occupied_ix
{
public:
  explicit Init_GlobalMap_occupied_ix(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_occupied_iy occupied_ix(::utils::msg::GlobalMap::_occupied_ix_type arg)
  {
    msg_.occupied_ix = std::move(arg);
    return Init_GlobalMap_occupied_iy(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_valid
{
public:
  explicit Init_GlobalMap_valid(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_occupied_ix valid(::utils::msg::GlobalMap::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_GlobalMap_occupied_ix(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_storage_path
{
public:
  explicit Init_GlobalMap_storage_path(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_valid storage_path(::utils::msg::GlobalMap::_storage_path_type arg)
  {
    msg_.storage_path = std::move(arg);
    return Init_GlobalMap_valid(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_explored_volume_m3
{
public:
  explicit Init_GlobalMap_explored_volume_m3(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_storage_path explored_volume_m3(::utils::msg::GlobalMap::_explored_volume_m3_type arg)
  {
    msg_.explored_volume_m3 = std::move(arg);
    return Init_GlobalMap_storage_path(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_unknown_voxels
{
public:
  explicit Init_GlobalMap_unknown_voxels(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_explored_volume_m3 unknown_voxels(::utils::msg::GlobalMap::_unknown_voxels_type arg)
  {
    msg_.unknown_voxels = std::move(arg);
    return Init_GlobalMap_explored_volume_m3(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_free_voxels
{
public:
  explicit Init_GlobalMap_free_voxels(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_unknown_voxels free_voxels(::utils::msg::GlobalMap::_free_voxels_type arg)
  {
    msg_.free_voxels = std::move(arg);
    return Init_GlobalMap_unknown_voxels(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_occupied_voxels
{
public:
  explicit Init_GlobalMap_occupied_voxels(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_free_voxels occupied_voxels(::utils::msg::GlobalMap::_occupied_voxels_type arg)
  {
    msg_.occupied_voxels = std::move(arg);
    return Init_GlobalMap_free_voxels(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_resolution
{
public:
  explicit Init_GlobalMap_resolution(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_occupied_voxels resolution(::utils::msg::GlobalMap::_resolution_type arg)
  {
    msg_.resolution = std::move(arg);
    return Init_GlobalMap_occupied_voxels(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_frame_id
{
public:
  explicit Init_GlobalMap_frame_id(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_resolution frame_id(::utils::msg::GlobalMap::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_GlobalMap_resolution(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_map_type
{
public:
  explicit Init_GlobalMap_map_type(::utils::msg::GlobalMap & msg)
  : msg_(msg)
  {}
  Init_GlobalMap_frame_id map_type(::utils::msg::GlobalMap::_map_type_type arg)
  {
    msg_.map_type = std::move(arg);
    return Init_GlobalMap_frame_id(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

class Init_GlobalMap_header
{
public:
  Init_GlobalMap_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GlobalMap_map_type header(::utils::msg::GlobalMap::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GlobalMap_map_type(msg_);
  }

private:
  ::utils::msg::GlobalMap msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::utils::msg::GlobalMap>()
{
  return utils::msg::builder::Init_GlobalMap_header();
}

}  // namespace utils

#endif  // UTILS__MSG__DETAIL__GLOBAL_MAP__BUILDER_HPP_
