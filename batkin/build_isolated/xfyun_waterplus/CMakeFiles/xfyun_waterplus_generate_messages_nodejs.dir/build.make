# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robot/batkin/src/xfyun_waterplus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robot/batkin/build_isolated/xfyun_waterplus

# Utility rule file for xfyun_waterplus_generate_messages_nodejs.

# Include the progress variables for this target.
include CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/progress.make

CMakeFiles/xfyun_waterplus_generate_messages_nodejs: /home/robot/batkin/devel_isolated/xfyun_waterplus/share/gennodejs/ros/xfyun_waterplus/srv/IATSwitch.js


/home/robot/batkin/devel_isolated/xfyun_waterplus/share/gennodejs/ros/xfyun_waterplus/srv/IATSwitch.js: /opt/ros/kinetic/lib/gennodejs/gen_nodejs.py
/home/robot/batkin/devel_isolated/xfyun_waterplus/share/gennodejs/ros/xfyun_waterplus/srv/IATSwitch.js: /home/robot/batkin/src/xfyun_waterplus/srv/IATSwitch.srv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/robot/batkin/build_isolated/xfyun_waterplus/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Javascript code from xfyun_waterplus/IATSwitch.srv"
	catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/kinetic/share/gennodejs/cmake/../../../lib/gennodejs/gen_nodejs.py /home/robot/batkin/src/xfyun_waterplus/srv/IATSwitch.srv -Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg -p xfyun_waterplus -o /home/robot/batkin/devel_isolated/xfyun_waterplus/share/gennodejs/ros/xfyun_waterplus/srv

xfyun_waterplus_generate_messages_nodejs: CMakeFiles/xfyun_waterplus_generate_messages_nodejs
xfyun_waterplus_generate_messages_nodejs: /home/robot/batkin/devel_isolated/xfyun_waterplus/share/gennodejs/ros/xfyun_waterplus/srv/IATSwitch.js
xfyun_waterplus_generate_messages_nodejs: CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/build.make

.PHONY : xfyun_waterplus_generate_messages_nodejs

# Rule to build all files generated by this target.
CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/build: xfyun_waterplus_generate_messages_nodejs

.PHONY : CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/build

CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/clean

CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/depend:
	cd /home/robot/batkin/build_isolated/xfyun_waterplus && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/batkin/src/xfyun_waterplus /home/robot/batkin/src/xfyun_waterplus /home/robot/batkin/build_isolated/xfyun_waterplus /home/robot/batkin/build_isolated/xfyun_waterplus /home/robot/batkin/build_isolated/xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xfyun_waterplus_generate_messages_nodejs.dir/depend
