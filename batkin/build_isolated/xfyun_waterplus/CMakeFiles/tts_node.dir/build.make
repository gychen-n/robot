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

# Include any dependencies generated for this target.
include CMakeFiles/tts_node.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tts_node.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tts_node.dir/flags.make

CMakeFiles/tts_node.dir/src/tts_node.cpp.o: CMakeFiles/tts_node.dir/flags.make
CMakeFiles/tts_node.dir/src/tts_node.cpp.o: /home/robot/batkin/src/xfyun_waterplus/src/tts_node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robot/batkin/build_isolated/xfyun_waterplus/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tts_node.dir/src/tts_node.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tts_node.dir/src/tts_node.cpp.o -c /home/robot/batkin/src/xfyun_waterplus/src/tts_node.cpp

CMakeFiles/tts_node.dir/src/tts_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tts_node.dir/src/tts_node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robot/batkin/src/xfyun_waterplus/src/tts_node.cpp > CMakeFiles/tts_node.dir/src/tts_node.cpp.i

CMakeFiles/tts_node.dir/src/tts_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tts_node.dir/src/tts_node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robot/batkin/src/xfyun_waterplus/src/tts_node.cpp -o CMakeFiles/tts_node.dir/src/tts_node.cpp.s

CMakeFiles/tts_node.dir/src/tts_node.cpp.o.requires:

.PHONY : CMakeFiles/tts_node.dir/src/tts_node.cpp.o.requires

CMakeFiles/tts_node.dir/src/tts_node.cpp.o.provides: CMakeFiles/tts_node.dir/src/tts_node.cpp.o.requires
	$(MAKE) -f CMakeFiles/tts_node.dir/build.make CMakeFiles/tts_node.dir/src/tts_node.cpp.o.provides.build
.PHONY : CMakeFiles/tts_node.dir/src/tts_node.cpp.o.provides

CMakeFiles/tts_node.dir/src/tts_node.cpp.o.provides.build: CMakeFiles/tts_node.dir/src/tts_node.cpp.o


# Object files for target tts_node
tts_node_OBJECTS = \
"CMakeFiles/tts_node.dir/src/tts_node.cpp.o"

# External object files for target tts_node
tts_node_EXTERNAL_OBJECTS =

/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: CMakeFiles/tts_node.dir/src/tts_node.cpp.o
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: CMakeFiles/tts_node.dir/build.make
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/libroscpp.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/librosconsole.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/librostime.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /opt/ros/kinetic/lib/libcpp_common.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node: CMakeFiles/tts_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robot/batkin/build_isolated/xfyun_waterplus/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tts_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tts_node.dir/build: /home/robot/batkin/devel_isolated/xfyun_waterplus/lib/xfyun_waterplus/tts_node

.PHONY : CMakeFiles/tts_node.dir/build

CMakeFiles/tts_node.dir/requires: CMakeFiles/tts_node.dir/src/tts_node.cpp.o.requires

.PHONY : CMakeFiles/tts_node.dir/requires

CMakeFiles/tts_node.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tts_node.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tts_node.dir/clean

CMakeFiles/tts_node.dir/depend:
	cd /home/robot/batkin/build_isolated/xfyun_waterplus && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/batkin/src/xfyun_waterplus /home/robot/batkin/src/xfyun_waterplus /home/robot/batkin/build_isolated/xfyun_waterplus /home/robot/batkin/build_isolated/xfyun_waterplus /home/robot/batkin/build_isolated/xfyun_waterplus/CMakeFiles/tts_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tts_node.dir/depend

