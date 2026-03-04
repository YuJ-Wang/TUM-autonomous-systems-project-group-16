// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from utils:msg/GlobalMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/global_map.hpp"


#ifndef UTILS__MSG__DETAIL__GLOBAL_MAP__STRUCT_HPP_
#define UTILS__MSG__DETAIL__GLOBAL_MAP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'frontier_goal'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__utils__msg__GlobalMap __attribute__((deprecated))
#else
# define DEPRECATED__utils__msg__GlobalMap __declspec(deprecated)
#endif

namespace utils
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GlobalMap_
{
  using Type = GlobalMap_<ContainerAllocator>;

  explicit GlobalMap_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    frontier_goal(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_type = "";
      this->frame_id = "";
      this->resolution = 0.0f;
      this->occupied_voxels = 0ul;
      this->free_voxels = 0ul;
      this->unknown_voxels = 0ul;
      this->explored_volume_m3 = 0.0f;
      this->storage_path = "";
      this->valid = false;
      this->frontier_goal_valid = false;
    }
  }

  explicit GlobalMap_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    map_type(_alloc),
    frame_id(_alloc),
    storage_path(_alloc),
    frontier_goal(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_type = "";
      this->frame_id = "";
      this->resolution = 0.0f;
      this->occupied_voxels = 0ul;
      this->free_voxels = 0ul;
      this->unknown_voxels = 0ul;
      this->explored_volume_m3 = 0.0f;
      this->storage_path = "";
      this->valid = false;
      this->frontier_goal_valid = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _map_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_type_type map_type;
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _resolution_type =
    float;
  _resolution_type resolution;
  using _occupied_voxels_type =
    uint32_t;
  _occupied_voxels_type occupied_voxels;
  using _free_voxels_type =
    uint32_t;
  _free_voxels_type free_voxels;
  using _unknown_voxels_type =
    uint32_t;
  _unknown_voxels_type unknown_voxels;
  using _explored_volume_m3_type =
    float;
  _explored_volume_m3_type explored_volume_m3;
  using _storage_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _storage_path_type storage_path;
  using _valid_type =
    bool;
  _valid_type valid;
  using _occupied_ix_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _occupied_ix_type occupied_ix;
  using _occupied_iy_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _occupied_iy_type occupied_iy;
  using _occupied_iz_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _occupied_iz_type occupied_iz;
  using _free_ix_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _free_ix_type free_ix;
  using _free_iy_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _free_iy_type free_iy;
  using _free_iz_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _free_iz_type free_iz;
  using _frontier_goal_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _frontier_goal_type frontier_goal;
  using _frontier_goal_valid_type =
    bool;
  _frontier_goal_valid_type frontier_goal_valid;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__map_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_type = _arg;
    return *this;
  }
  Type & set__frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__resolution(
    const float & _arg)
  {
    this->resolution = _arg;
    return *this;
  }
  Type & set__occupied_voxels(
    const uint32_t & _arg)
  {
    this->occupied_voxels = _arg;
    return *this;
  }
  Type & set__free_voxels(
    const uint32_t & _arg)
  {
    this->free_voxels = _arg;
    return *this;
  }
  Type & set__unknown_voxels(
    const uint32_t & _arg)
  {
    this->unknown_voxels = _arg;
    return *this;
  }
  Type & set__explored_volume_m3(
    const float & _arg)
  {
    this->explored_volume_m3 = _arg;
    return *this;
  }
  Type & set__storage_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->storage_path = _arg;
    return *this;
  }
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
    return *this;
  }
  Type & set__occupied_ix(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->occupied_ix = _arg;
    return *this;
  }
  Type & set__occupied_iy(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->occupied_iy = _arg;
    return *this;
  }
  Type & set__occupied_iz(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->occupied_iz = _arg;
    return *this;
  }
  Type & set__free_ix(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->free_ix = _arg;
    return *this;
  }
  Type & set__free_iy(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->free_iy = _arg;
    return *this;
  }
  Type & set__free_iz(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->free_iz = _arg;
    return *this;
  }
  Type & set__frontier_goal(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->frontier_goal = _arg;
    return *this;
  }
  Type & set__frontier_goal_valid(
    const bool & _arg)
  {
    this->frontier_goal_valid = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    utils::msg::GlobalMap_<ContainerAllocator> *;
  using ConstRawPtr =
    const utils::msg::GlobalMap_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<utils::msg::GlobalMap_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<utils::msg::GlobalMap_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      utils::msg::GlobalMap_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<utils::msg::GlobalMap_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      utils::msg::GlobalMap_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<utils::msg::GlobalMap_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<utils::msg::GlobalMap_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<utils::msg::GlobalMap_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__utils__msg__GlobalMap
    std::shared_ptr<utils::msg::GlobalMap_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__utils__msg__GlobalMap
    std::shared_ptr<utils::msg::GlobalMap_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GlobalMap_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->map_type != other.map_type) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->resolution != other.resolution) {
      return false;
    }
    if (this->occupied_voxels != other.occupied_voxels) {
      return false;
    }
    if (this->free_voxels != other.free_voxels) {
      return false;
    }
    if (this->unknown_voxels != other.unknown_voxels) {
      return false;
    }
    if (this->explored_volume_m3 != other.explored_volume_m3) {
      return false;
    }
    if (this->storage_path != other.storage_path) {
      return false;
    }
    if (this->valid != other.valid) {
      return false;
    }
    if (this->occupied_ix != other.occupied_ix) {
      return false;
    }
    if (this->occupied_iy != other.occupied_iy) {
      return false;
    }
    if (this->occupied_iz != other.occupied_iz) {
      return false;
    }
    if (this->free_ix != other.free_ix) {
      return false;
    }
    if (this->free_iy != other.free_iy) {
      return false;
    }
    if (this->free_iz != other.free_iz) {
      return false;
    }
    if (this->frontier_goal != other.frontier_goal) {
      return false;
    }
    if (this->frontier_goal_valid != other.frontier_goal_valid) {
      return false;
    }
    return true;
  }
  bool operator!=(const GlobalMap_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GlobalMap_

// alias to use template instance with default allocator
using GlobalMap =
  utils::msg::GlobalMap_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace utils

#endif  // UTILS__MSG__DETAIL__GLOBAL_MAP__STRUCT_HPP_
