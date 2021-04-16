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
include examples/CMakeFiles/circle_fit.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/circle_fit.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/circle_fit.dir/flags.make

examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o: examples/CMakeFiles/circle_fit.dir/flags.make
examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o: /home/robot/batkin/src/mapping/ceres-solver/examples/circle_fit.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robot/batkin/build_isolated/ceres-solver/devel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/circle_fit.dir/circle_fit.cc.o -c /home/robot/batkin/src/mapping/ceres-solver/examples/circle_fit.cc

examples/CMakeFiles/circle_fit.dir/circle_fit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/circle_fit.dir/circle_fit.cc.i"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robot/batkin/src/mapping/ceres-solver/examples/circle_fit.cc > CMakeFiles/circle_fit.dir/circle_fit.cc.i

examples/CMakeFiles/circle_fit.dir/circle_fit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/circle_fit.dir/circle_fit.cc.s"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robot/batkin/src/mapping/ceres-solver/examples/circle_fit.cc -o CMakeFiles/circle_fit.dir/circle_fit.cc.s

examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.requires:

.PHONY : examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.requires

examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.provides: examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.requires
	$(MAKE) -f examples/CMakeFiles/circle_fit.dir/build.make examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.provides.build
.PHONY : examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.provides

examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.provides.build: examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o


# Object files for target circle_fit
circle_fit_OBJECTS = \
"CMakeFiles/circle_fit.dir/circle_fit.cc.o"

# External object files for target circle_fit
circle_fit_EXTERNAL_OBJECTS =

bin/circle_fit: examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o
bin/circle_fit: examples/CMakeFiles/circle_fit.dir/build.make
bin/circle_fit: lib/libceres.a
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libgflags.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libglog.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libgflags.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libspqr.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libtbb.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libcholmod.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libccolamd.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libcamd.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libcolamd.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libamd.so
bin/circle_fit: /usr/lib/liblapack.so
bin/circle_fit: /usr/lib/libf77blas.so
bin/circle_fit: /usr/lib/libatlas.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/librt.so
bin/circle_fit: /usr/local/lib/libmetis.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/circle_fit: /usr/lib/liblapack.so
bin/circle_fit: /usr/lib/libf77blas.so
bin/circle_fit: /usr/lib/libatlas.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/librt.so
bin/circle_fit: /usr/local/lib/libmetis.so
bin/circle_fit: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/circle_fit: examples/CMakeFiles/circle_fit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robot/batkin/build_isolated/ceres-solver/devel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/circle_fit"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/circle_fit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/circle_fit.dir/build: bin/circle_fit

.PHONY : examples/CMakeFiles/circle_fit.dir/build

examples/CMakeFiles/circle_fit.dir/requires: examples/CMakeFiles/circle_fit.dir/circle_fit.cc.o.requires

.PHONY : examples/CMakeFiles/circle_fit.dir/requires

examples/CMakeFiles/circle_fit.dir/clean:
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/examples && $(CMAKE_COMMAND) -P CMakeFiles/circle_fit.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/circle_fit.dir/clean

examples/CMakeFiles/circle_fit.dir/depend:
	cd /home/robot/batkin/build_isolated/ceres-solver/devel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/batkin/src/mapping/ceres-solver /home/robot/batkin/src/mapping/ceres-solver/examples /home/robot/batkin/build_isolated/ceres-solver/devel /home/robot/batkin/build_isolated/ceres-solver/devel/examples /home/robot/batkin/build_isolated/ceres-solver/devel/examples/CMakeFiles/circle_fit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/circle_fit.dir/depend

