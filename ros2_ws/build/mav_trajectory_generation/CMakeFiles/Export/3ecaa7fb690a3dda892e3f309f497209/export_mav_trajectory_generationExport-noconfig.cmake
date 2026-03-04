#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mav_trajectory_generation::mav_trajectory_generation" for configuration ""
set_property(TARGET mav_trajectory_generation::mav_trajectory_generation APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mav_trajectory_generation::mav_trajectory_generation PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmav_trajectory_generation.so"
  IMPORTED_SONAME_NOCONFIG "libmav_trajectory_generation.so"
  )

list(APPEND _cmake_import_check_targets mav_trajectory_generation::mav_trajectory_generation )
list(APPEND _cmake_import_check_files_for_mav_trajectory_generation::mav_trajectory_generation "${_IMPORT_PREFIX}/lib/libmav_trajectory_generation.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
