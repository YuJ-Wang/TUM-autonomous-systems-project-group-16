// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from utils:msg/GlobalMap.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "utils/msg/global_map.hpp"


#ifndef UTILS__MSG__DETAIL__GLOBAL_MAP__TRAITS_HPP_
#define UTILS__MSG__DETAIL__GLOBAL_MAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "utils/msg/detail/global_map__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'frontier_goal'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace utils
{

namespace msg
{

inline void to_flow_style_yaml(
  const GlobalMap & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: map_type
  {
    out << "map_type: ";
    rosidl_generator_traits::value_to_yaml(msg.map_type, out);
    out << ", ";
  }

  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: resolution
  {
    out << "resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.resolution, out);
    out << ", ";
  }

  // member: occupied_voxels
  {
    out << "occupied_voxels: ";
    rosidl_generator_traits::value_to_yaml(msg.occupied_voxels, out);
    out << ", ";
  }

  // member: free_voxels
  {
    out << "free_voxels: ";
    rosidl_generator_traits::value_to_yaml(msg.free_voxels, out);
    out << ", ";
  }

  // member: unknown_voxels
  {
    out << "unknown_voxels: ";
    rosidl_generator_traits::value_to_yaml(msg.unknown_voxels, out);
    out << ", ";
  }

  // member: explored_volume_m3
  {
    out << "explored_volume_m3: ";
    rosidl_generator_traits::value_to_yaml(msg.explored_volume_m3, out);
    out << ", ";
  }

  // member: storage_path
  {
    out << "storage_path: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_path, out);
    out << ", ";
  }

  // member: valid
  {
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << ", ";
  }

  // member: occupied_ix
  {
    if (msg.occupied_ix.size() == 0) {
      out << "occupied_ix: []";
    } else {
      out << "occupied_ix: [";
      size_t pending_items = msg.occupied_ix.size();
      for (auto item : msg.occupied_ix) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: occupied_iy
  {
    if (msg.occupied_iy.size() == 0) {
      out << "occupied_iy: []";
    } else {
      out << "occupied_iy: [";
      size_t pending_items = msg.occupied_iy.size();
      for (auto item : msg.occupied_iy) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: occupied_iz
  {
    if (msg.occupied_iz.size() == 0) {
      out << "occupied_iz: []";
    } else {
      out << "occupied_iz: [";
      size_t pending_items = msg.occupied_iz.size();
      for (auto item : msg.occupied_iz) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: free_ix
  {
    if (msg.free_ix.size() == 0) {
      out << "free_ix: []";
    } else {
      out << "free_ix: [";
      size_t pending_items = msg.free_ix.size();
      for (auto item : msg.free_ix) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: free_iy
  {
    if (msg.free_iy.size() == 0) {
      out << "free_iy: []";
    } else {
      out << "free_iy: [";
      size_t pending_items = msg.free_iy.size();
      for (auto item : msg.free_iy) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: free_iz
  {
    if (msg.free_iz.size() == 0) {
      out << "free_iz: []";
    } else {
      out << "free_iz: [";
      size_t pending_items = msg.free_iz.size();
      for (auto item : msg.free_iz) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: frontier_goal
  {
    out << "frontier_goal: ";
    to_flow_style_yaml(msg.frontier_goal, out);
    out << ", ";
  }

  // member: frontier_goal_valid
  {
    out << "frontier_goal_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.frontier_goal_valid, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GlobalMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: map_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_type: ";
    rosidl_generator_traits::value_to_yaml(msg.map_type, out);
    out << "\n";
  }

  // member: frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << "\n";
  }

  // member: resolution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.resolution, out);
    out << "\n";
  }

  // member: occupied_voxels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "occupied_voxels: ";
    rosidl_generator_traits::value_to_yaml(msg.occupied_voxels, out);
    out << "\n";
  }

  // member: free_voxels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "free_voxels: ";
    rosidl_generator_traits::value_to_yaml(msg.free_voxels, out);
    out << "\n";
  }

  // member: unknown_voxels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "unknown_voxels: ";
    rosidl_generator_traits::value_to_yaml(msg.unknown_voxels, out);
    out << "\n";
  }

  // member: explored_volume_m3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "explored_volume_m3: ";
    rosidl_generator_traits::value_to_yaml(msg.explored_volume_m3, out);
    out << "\n";
  }

  // member: storage_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "storage_path: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_path, out);
    out << "\n";
  }

  // member: valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << "\n";
  }

  // member: occupied_ix
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.occupied_ix.size() == 0) {
      out << "occupied_ix: []\n";
    } else {
      out << "occupied_ix:\n";
      for (auto item : msg.occupied_ix) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: occupied_iy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.occupied_iy.size() == 0) {
      out << "occupied_iy: []\n";
    } else {
      out << "occupied_iy:\n";
      for (auto item : msg.occupied_iy) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: occupied_iz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.occupied_iz.size() == 0) {
      out << "occupied_iz: []\n";
    } else {
      out << "occupied_iz:\n";
      for (auto item : msg.occupied_iz) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: free_ix
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.free_ix.size() == 0) {
      out << "free_ix: []\n";
    } else {
      out << "free_ix:\n";
      for (auto item : msg.free_ix) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: free_iy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.free_iy.size() == 0) {
      out << "free_iy: []\n";
    } else {
      out << "free_iy:\n";
      for (auto item : msg.free_iy) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: free_iz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.free_iz.size() == 0) {
      out << "free_iz: []\n";
    } else {
      out << "free_iz:\n";
      for (auto item : msg.free_iz) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: frontier_goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frontier_goal:\n";
    to_block_style_yaml(msg.frontier_goal, out, indentation + 2);
  }

  // member: frontier_goal_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frontier_goal_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.frontier_goal_valid, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GlobalMap & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace utils

namespace rosidl_generator_traits
{

[[deprecated("use utils::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const utils::msg::GlobalMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  utils::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use utils::msg::to_yaml() instead")]]
inline std::string to_yaml(const utils::msg::GlobalMap & msg)
{
  return utils::msg::to_yaml(msg);
}

template<>
inline const char * data_type<utils::msg::GlobalMap>()
{
  return "utils::msg::GlobalMap";
}

template<>
inline const char * name<utils::msg::GlobalMap>()
{
  return "utils/msg/GlobalMap";
}

template<>
struct has_fixed_size<utils::msg::GlobalMap>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<utils::msg::GlobalMap>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<utils::msg::GlobalMap>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UTILS__MSG__DETAIL__GLOBAL_MAP__TRAITS_HPP_
