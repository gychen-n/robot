# generated from catkin/cmake/template/pkgConfig.cmake.in

# append elements to a list and remove existing duplicates from the list
# copied from catkin/cmake/list_append_deduplicate.cmake to keep pkgConfig
# self contained
macro(_list_append_deduplicate listname)
  if(NOT "${ARGN}" STREQUAL "")
    if(${listname})
      list(REMOVE_ITEM ${listname} ${ARGN})
    endif()
    list(APPEND ${listname} ${ARGN})
  endif()
endmacro()

# append elements to a list if they are not already in the list
# copied from catkin/cmake/list_append_unique.cmake to keep pkgConfig
# self contained
macro(_list_append_unique listname)
  foreach(_item ${ARGN})
    list(FIND ${listname} ${_item} _index)
    if(_index EQUAL -1)
      list(APPEND ${listname} ${_item})
    endif()
  endforeach()
endmacro()

# pack a list of libraries with optional build configuration keywords
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_pack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  set(_argn ${ARGN})
  list(LENGTH _argn _count)
  set(_index 0)
  while(${_index} LESS ${_count})
    list(GET _argn ${_index} lib)
    if("${lib}" MATCHES "^(debug|optimized|general)$")
      math(EXPR _index "${_index} + 1")
      if(${_index} EQUAL ${_count})
        message(FATAL_ERROR "_pack_libraries_with_build_configuration() the list of libraries '${ARGN}' ends with '${lib}' which is a build configuration keyword and must be followed by a library")
      endif()
      list(GET _argn ${_index} library)
      list(APPEND ${VAR} "${lib}${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}${library}")
    else()
      list(APPEND ${VAR} "${lib}")
    endif()
    math(EXPR _index "${_index} + 1")
  endwhile()
endmacro()

# unpack a list of libraries with optional build configuration keyword prefixes
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_unpack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  foreach(lib ${ARGN})
    string(REGEX REPLACE "^(debug|optimized|general)${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}(.+)$" "\\1;\\2" lib "${lib}")
    list(APPEND ${VAR} "${lib}")
  endforeach()
endmacro()


if(xfyun_waterplus_CONFIG_INCLUDED)
  return()
endif()
set(xfyun_waterplus_CONFIG_INCLUDED TRUE)

# set variables for source/devel/install prefixes
if("FALSE" STREQUAL "TRUE")
  set(xfyun_waterplus_SOURCE_PREFIX /home/robot/batkin/src/xfyun_waterplus)
  set(xfyun_waterplus_DEVEL_PREFIX /home/robot/batkin/devel_isolated/xfyun_waterplus)
  set(xfyun_waterplus_INSTALL_PREFIX "")
  set(xfyun_waterplus_PREFIX ${xfyun_waterplus_DEVEL_PREFIX})
else()
  set(xfyun_waterplus_SOURCE_PREFIX "")
  set(xfyun_waterplus_DEVEL_PREFIX "")
  set(xfyun_waterplus_INSTALL_PREFIX /home/robot/batkin/install_isolated)
  set(xfyun_waterplus_PREFIX ${xfyun_waterplus_INSTALL_PREFIX})
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "WARNING: package 'xfyun_waterplus' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message("${_msg}")
endif()

# flag project as catkin-based to distinguish if a find_package()-ed project is a catkin project
set(xfyun_waterplus_FOUND_CATKIN_PROJECT TRUE)

if(NOT "include " STREQUAL " ")
  set(xfyun_waterplus_INCLUDE_DIRS "")
  set(_include_dirs "include")
  if(NOT " " STREQUAL " ")
    set(_report "Check the issue tracker '' and consider creating a ticket if the problem has not been reported yet.")
  elseif(NOT "http://www.xfyun.cn, http://www.6-robot.com " STREQUAL " ")
    set(_report "Check the website 'http://www.xfyun.cn, http://www.6-robot.com' for information and consider reporting the problem.")
  else()
    set(_report "Report the problem to the maintainer 'Zhang Wanjie <zhangwanjie@6-robot.com>' and request to fix the problem.")
  endif()
  foreach(idir ${_include_dirs})
    if(IS_ABSOLUTE ${idir} AND IS_DIRECTORY ${idir})
      set(include ${idir})
    elseif("${idir} " STREQUAL "include ")
      get_filename_component(include "${xfyun_waterplus_DIR}/../../../include" ABSOLUTE)
      if(NOT IS_DIRECTORY ${include})
        message(FATAL_ERROR "Project 'xfyun_waterplus' specifies '${idir}' as an include dir, which is not found.  It does not exist in '${include}'.  ${_report}")
      endif()
    else()
      message(FATAL_ERROR "Project 'xfyun_waterplus' specifies '${idir}' as an include dir, which is not found.  It does neither exist as an absolute directory nor in '\${prefix}/${idir}'.  ${_report}")
    endif()
    _list_append_unique(xfyun_waterplus_INCLUDE_DIRS ${include})
  endforeach()
endif()

set(libraries "")
foreach(library ${libraries})
  # keep build configuration keywords, target names and absolute libraries as-is
  if("${library}" MATCHES "^(debug|optimized|general)$")
    list(APPEND xfyun_waterplus_LIBRARIES ${library})
  elseif(${library} MATCHES "^-l")
    list(APPEND xfyun_waterplus_LIBRARIES ${library})
  elseif(${library} MATCHES "^-")
    # This is a linker flag/option (like -pthread)
    # There's no standard variable for these, so create an interface library to hold it
    if(NOT xfyun_waterplus_NUM_DUMMY_TARGETS)
      set(xfyun_waterplus_NUM_DUMMY_TARGETS 0)
    endif()
    # Make sure the target name is unique
    set(interface_target_name "catkin::xfyun_waterplus::wrapped-linker-option${xfyun_waterplus_NUM_DUMMY_TARGETS}")
    while(TARGET "${interface_target_name}")
      math(EXPR xfyun_waterplus_NUM_DUMMY_TARGETS "${xfyun_waterplus_NUM_DUMMY_TARGETS}+1")
      set(interface_target_name "catkin::xfyun_waterplus::wrapped-linker-option${xfyun_waterplus_NUM_DUMMY_TARGETS}")
    endwhile()
    add_library("${interface_target_name}" INTERFACE IMPORTED)
    if("${CMAKE_VERSION}" VERSION_LESS "3.13.0")
      set_property(
        TARGET
        "${interface_target_name}"
        APPEND PROPERTY
        INTERFACE_LINK_LIBRARIES "${library}")
    else()
      target_link_options("${interface_target_name}" INTERFACE "${library}")
    endif()
    list(APPEND xfyun_waterplus_LIBRARIES "${interface_target_name}")
  elseif(TARGET ${library})
    list(APPEND xfyun_waterplus_LIBRARIES ${library})
  elseif(IS_ABSOLUTE ${library})
    list(APPEND xfyun_waterplus_LIBRARIES ${library})
  else()
    set(lib_path "")
    set(lib "${library}-NOTFOUND")
    # since the path where the library is found is returned we have to iterate over the paths manually
    foreach(path /home/robot/batkin/install_isolated/lib;/home/robot/batkin/devel_isolated/waterplus_map_tools/lib;/home/robot/batkin/devel_isolated/teb_local_planner/lib;/home/robot/batkin/devel_isolated/move_base/lib;/home/robot/batkin/devel_isolated/rotate_recovery/lib;/home/robot/batkin/devel_isolated/record_path_planner/lib;/home/robot/batkin/devel_isolated/global_planner/lib;/home/robot/batkin/devel_isolated/navfn/lib;/home/robot/batkin/devel_isolated/move_slow_and_clear/lib;/home/robot/batkin/devel_isolated/loop_path_planner/lib;/home/robot/batkin/devel_isolated/dwa_local_planner/lib;/home/robot/batkin/devel_isolated/clear_costmap_recovery/lib;/home/robot/batkin/devel_isolated/carrot_planner/lib;/home/robot/batkin/devel_isolated/base_local_planner/lib;/home/robot/batkin/devel_isolated/nav_core/lib;/home/robot/batkin/devel_isolated/costmap_2d/lib;/home/robot/batkin/devel_isolated/voxel_grid/lib;/home/robot/batkin/devel_isolated/turtlebot_teleop/lib;/home/robot/batkin/devel_isolated/turtlebot_rapps/lib;/home/robot/batkin/devel_isolated/turtlebot_navigation/lib;/home/robot/batkin/devel_isolated/turtlebot_follower/lib;/home/robot/batkin/devel_isolated/turtlebot_description/lib;/home/robot/batkin/devel_isolated/turtlebot_capabilities/lib;/home/robot/batkin/devel_isolated/turtlebot_calibration/lib;/home/robot/batkin/devel_isolated/turtlebot_bringup/lib;/home/robot/batkin/devel_isolated/turtlebot_apps/lib;/home/robot/batkin/devel_isolated/turtlebot_actions/lib;/home/robot/batkin/devel_isolated/turtlebot/lib;/home/robot/batkin/devel_isolated/tl740d/lib;/home/robot/batkin/devel_isolated/stim/lib;/home/robot/batkin/devel_isolated/stereo_image_proc/lib;/home/robot/batkin/devel_isolated/spacenav_node/lib;/home/robot/batkin/devel_isolated/slam_gmapping/lib;/home/robot/batkin/devel_isolated/simulation_launch/lib;/home/robot/batkin/devel_isolated/rviz_imu_plugin/lib;/home/robot/batkin/devel_isolated/rslidar_sync/lib;/home/robot/batkin/devel_isolated/rslidar_pointcloud/lib;/home/robot/batkin/devel_isolated/rslidar_driver/lib;/home/robot/batkin/devel_isolated/rslidar_msgs/lib;/home/robot/batkin/devel_isolated/rslidar/lib;/home/robot/batkin/devel_isolated/rbx1_apps/lib;/home/robot/batkin/devel_isolated/ps3joy/lib;/home/robot/batkin/devel_isolated/pointcloud_to_laserscan/lib;/home/robot/batkin/devel_isolated/path_rviz_plugin/lib;/home/robot/batkin/devel_isolated/path_server/lib;/home/robot/batkin/devel_isolated/gmapping/lib;/home/robot/batkin/devel_isolated/openslam_gmapping/lib;/home/robot/batkin/devel_isolated/navigation/lib;/home/robot/batkin/devel_isolated/map_server/lib;/home/robot/batkin/devel_isolated/location_fusion/lib;/home/robot/batkin/devel_isolated/joystick_drivers/lib;/home/robot/batkin/devel_isolated/joy_to_twist/lib;/home/robot/batkin/devel_isolated/joy/lib;/home/robot/batkin/devel_isolated/image_view/lib;/home/robot/batkin/devel_isolated/image_rotate/lib;/home/robot/batkin/devel_isolated/image_publisher/lib;/home/robot/batkin/devel_isolated/image_proc/lib;/home/robot/batkin/devel_isolated/image_pipeline/lib;/home/robot/batkin/devel_isolated/freenect_stack/lib;/home/robot/batkin/devel_isolated/freenect_launch/lib;/home/robot/batkin/devel_isolated/freenect_camera/lib;/home/robot/batkin/devel_isolated/fake_localization/lib;/home/robot/batkin/devel_isolated/depth_image_proc/lib;/home/robot/batkin/devel_isolated/dashgo_driver/lib;/home/robot/batkin/devel_isolated/cartographer_rviz/lib;/home/robot/batkin/devel_isolated/cartographer_ros/lib;/home/robot/batkin/devel_isolated/cartographer_ros_msgs/lib;/home/robot/batkin/devel_isolated/camera_calibration/lib;/home/robot/batkin/devel_isolated/autolabor_test_launch/lib;/home/robot/batkin/devel_isolated/autolabor_simulation_object/lib;/home/robot/batkin/devel_isolated/autolabor_simulation_stage/lib;/home/robot/batkin/devel_isolated/autolabor_simulation_location/lib;/home/robot/batkin/devel_isolated/autolabor_simulation_lidar/lib;/home/robot/batkin/devel_isolated/autolabor_simulation_base/lib;/home/robot/batkin/devel_isolated/autolabor_navigation_launch/lib;/home/robot/batkin/devel_isolated/autolabor_keyboard_control/lib;/home/robot/batkin/devel_isolated/autolabor_description/lib;/home/robot/batkin/devel_isolated/ah100b/lib;/home/robot/catkin_ws/devel/lib;/opt/ros/kinetic/lib)
      find_library(lib ${library}
        PATHS ${path}
        NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
      if(lib)
        set(lib_path ${path})
        break()
      endif()
    endforeach()
    if(lib)
      _list_append_unique(xfyun_waterplus_LIBRARY_DIRS ${lib_path})
      list(APPEND xfyun_waterplus_LIBRARIES ${lib})
    else()
      # as a fall back for non-catkin libraries try to search globally
      find_library(lib ${library})
      if(NOT lib)
        message(FATAL_ERROR "Project '${PROJECT_NAME}' tried to find library '${library}'.  The library is neither a target nor built/installed properly.  Did you compile project 'xfyun_waterplus'?  Did you find_package() it before the subdirectory containing its code is included?")
      endif()
      list(APPEND xfyun_waterplus_LIBRARIES ${lib})
    endif()
  endif()
endforeach()

set(xfyun_waterplus_EXPORTED_TARGETS "xfyun_waterplus_generate_messages_cpp;xfyun_waterplus_generate_messages_eus;xfyun_waterplus_generate_messages_lisp;xfyun_waterplus_generate_messages_nodejs;xfyun_waterplus_generate_messages_py")
# create dummy targets for exported code generation targets to make life of users easier
foreach(t ${xfyun_waterplus_EXPORTED_TARGETS})
  if(NOT TARGET ${t})
    add_custom_target(${t})
  endif()
endforeach()

set(depends "message_runtime")
foreach(depend ${depends})
  string(REPLACE " " ";" depend_list ${depend})
  # the package name of the dependency must be kept in a unique variable so that it is not overwritten in recursive calls
  list(GET depend_list 0 xfyun_waterplus_dep)
  list(LENGTH depend_list count)
  if(${count} EQUAL 1)
    # simple dependencies must only be find_package()-ed once
    if(NOT ${xfyun_waterplus_dep}_FOUND)
      find_package(${xfyun_waterplus_dep} REQUIRED NO_MODULE)
    endif()
  else()
    # dependencies with components must be find_package()-ed again
    list(REMOVE_AT depend_list 0)
    find_package(${xfyun_waterplus_dep} REQUIRED NO_MODULE ${depend_list})
  endif()
  _list_append_unique(xfyun_waterplus_INCLUDE_DIRS ${${xfyun_waterplus_dep}_INCLUDE_DIRS})

  # merge build configuration keywords with library names to correctly deduplicate
  _pack_libraries_with_build_configuration(xfyun_waterplus_LIBRARIES ${xfyun_waterplus_LIBRARIES})
  _pack_libraries_with_build_configuration(_libraries ${${xfyun_waterplus_dep}_LIBRARIES})
  _list_append_deduplicate(xfyun_waterplus_LIBRARIES ${_libraries})
  # undo build configuration keyword merging after deduplication
  _unpack_libraries_with_build_configuration(xfyun_waterplus_LIBRARIES ${xfyun_waterplus_LIBRARIES})

  _list_append_unique(xfyun_waterplus_LIBRARY_DIRS ${${xfyun_waterplus_dep}_LIBRARY_DIRS})
  list(APPEND xfyun_waterplus_EXPORTED_TARGETS ${${xfyun_waterplus_dep}_EXPORTED_TARGETS})
endforeach()

set(pkg_cfg_extras "xfyun_waterplus-msg-extras.cmake")
foreach(extra ${pkg_cfg_extras})
  if(NOT IS_ABSOLUTE ${extra})
    set(extra ${xfyun_waterplus_DIR}/${extra})
  endif()
  include(${extra})
endforeach()
