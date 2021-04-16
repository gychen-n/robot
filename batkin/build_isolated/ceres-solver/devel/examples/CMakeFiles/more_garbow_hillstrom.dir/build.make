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
CMAKE_SOURCE_DIR = /home/robot/batkin/src/mapping/ceres-solver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robot/batkin/build_isolated/ceres-solver/devel

# Include any dependencies generated for this target.
include examples/CMakeFiles/more_garbow_hillstrom.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/more_garbow_hillstrom.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/more_garbow_hillstrom.dir/flags.make

examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o: examples/CMakeFiles/more_garbow_hillstrom.dir/flags.make
examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o: /home/robot/batkin/src/mapping/ceres-solver/examples/more_garbow_hillstrom.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robot/batkin/build_isolated/ceres-solver/devel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o -c /home/robot/batkin/src/mapping/ceres-solver/examples/more_garbow_hillstrom.cc

examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.i"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robot/batkin/src/mapping/ceres-solver/examples/more_garbow_hillstrom.cc > CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.i

examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.s"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robot/batkin/src/mapping/ceres-solver/examples/more_garbow_hillstrom.cc -o CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.s

examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.requires:

.PHONY : examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.requires

examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.provides: examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.requires
	$(MAKE) -f examples/CMakeFiles/more_garbow_hillstrom.dir/build.make examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.provides.build
.PHONY : examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.provides

examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.provides.build: examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o


# Object files for target more_garbow_hillstrom
more_garbow_hillstrom_OBJECTS = \
"CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o"

# External object files for target more_garbow_hillstrom
more_garbow_hillstrom_EXTERNAL_OBJECTS =

bin/more_garbow_hillstrom: examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o
bin/more_garbow_hillstrom: examples/CMakeFiles/more_garbow_hillstrom.dir/build.make
bin/more_garbow_hillstrom: lib/libceres.a
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libgflags.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libglog.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libgflags.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libspqr.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libtbb.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libcholmod.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libccolamd.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libcamd.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libcolamd.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libamd.so
bin/more_garbow_hillstrom: /usr/lib/liblapack.so
bin/more_garbow_hillstrom: /usr/lib/libf77blas.so
bin/more_garbow_hillstrom: /usr/lib/libatlas.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/librt.so
bin/more_garbow_hillstrom: /usr/local/lib/libmetis.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/more_garbow_hillstrom: /usr/lib/liblapack.so
bin/more_garbow_hillstrom: /usr/lib/libf77blas.so
bin/more_garbow_hillstrom: /usr/lib/libatlas.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/librt.so
bin/more_garbow_hillstrom: /usr/local/lib/libmetis.so
bin/more_garbow_hillstrom: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/more_garbow_hillstrom: examples/CMakeFiles/more_garbow_hillstrom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robot/batkin/build_isolated/ceres-solver/devel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/more_garbow_hillstrom"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/more_garbow_hillstrom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/more_garbow_hillstrom.dir/build: bin/more_garbow_hillstrom

.PHONY : examples/CMakeFiles/more_garbow_hillstrom.dir/build

examples/CMakeFiles/more_garbow_hillstrom.dir/requires: examples/CMakeFiles/more_garbow_hillstrom.dir/more_garbow_hillstrom.cc.o.requires

.PHONY : examples/CMakeFiles/more_garbow_hillstrom.dir/requires

examples/CMakeFiles/more_garbow_hillstrom.dir/clean:
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && $(CMAKE_COMMAND) -P CMakeFiles/more_garbow_hillstrom.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/more_garbow_hillstrom.dir/clean

examples/CMakeFiles/more_garbow_hillstrom.dir/depend:
	cd /home/robot/batkin/build_isolated/ceres-solver/devel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/batkin/src/mapping/ceres-solver /home/robot/batkin/src/mapping/ceres-solver/examples /home/robot/batkin/build_isolated/ceres-solver/devel /home/robot/batkin/build_isolated/ceres-solver/devel/examples /home/robot/batkin/build_isolated/ceres-solver/devel/examples/CMakeFiles/more_garbow_hillstrom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/more_garbow_hillstrom.dir/depend
