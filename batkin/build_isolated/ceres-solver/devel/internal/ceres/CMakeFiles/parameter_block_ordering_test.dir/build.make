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
include internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/depend.make

# Include the progress variables for this target.
include internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/progress.make

# Include the compile flags for this target's objects.
include internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/flags.make

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/flags.make
internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o: /home/robot/batkin/src/mapping/ceres-solver/internal/ceres/parameter_block_ordering_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robot/batkin/build_isolated/ceres-solver/devel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o -c /home/robot/batkin/src/mapping/ceres-solver/internal/ceres/parameter_block_ordering_test.cc

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.i"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robot/batkin/src/mapping/ceres-solver/internal/ceres/parameter_block_ordering_test.cc > CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.i

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.s"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robot/batkin/src/mapping/ceres-solver/internal/ceres/parameter_block_ordering_test.cc -o CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.s

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.requires:

.PHONY : internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.requires

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.provides: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.requires
	$(MAKE) -f internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/build.make internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.provides.build
.PHONY : internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.provides

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.provides.build: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o


# Object files for target parameter_block_ordering_test
parameter_block_ordering_test_OBJECTS = \
"CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o"

# External object files for target parameter_block_ordering_test
parameter_block_ordering_test_EXTERNAL_OBJECTS =

bin/parameter_block_ordering_test: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o
bin/parameter_block_ordering_test: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/build.make
bin/parameter_block_ordering_test: lib/libtest_util.a
bin/parameter_block_ordering_test: lib/libceres.a
bin/parameter_block_ordering_test: lib/libgtest.a
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libspqr.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libtbb.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libcholmod.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libccolamd.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libcamd.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libcolamd.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libamd.so
bin/parameter_block_ordering_test: /usr/lib/liblapack.so
bin/parameter_block_ordering_test: /usr/lib/libf77blas.so
bin/parameter_block_ordering_test: /usr/lib/libatlas.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/librt.so
bin/parameter_block_ordering_test: /usr/local/lib/libmetis.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/parameter_block_ordering_test: /usr/lib/liblapack.so
bin/parameter_block_ordering_test: /usr/lib/libf77blas.so
bin/parameter_block_ordering_test: /usr/lib/libatlas.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/librt.so
bin/parameter_block_ordering_test: /usr/local/lib/libmetis.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libcxsparse.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libgflags.so
bin/parameter_block_ordering_test: /usr/lib/x86_64-linux-gnu/libglog.so
bin/parameter_block_ordering_test: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robot/batkin/build_isolated/ceres-solver/devel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/parameter_block_ordering_test"
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parameter_block_ordering_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/build: bin/parameter_block_ordering_test

.PHONY : internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/build

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/requires: internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/parameter_block_ordering_test.cc.o.requires

.PHONY : internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/requires

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/clean:
	cd /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres && $(CMAKE_COMMAND) -P CMakeFiles/parameter_block_ordering_test.dir/cmake_clean.cmake
.PHONY : internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/clean

internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/depend:
	cd /home/robot/batkin/build_isolated/ceres-solver/devel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robot/batkin/src/mapping/ceres-solver /home/robot/batkin/src/mapping/ceres-solver/internal/ceres /home/robot/batkin/build_isolated/ceres-solver/devel /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres /home/robot/batkin/build_isolated/ceres-solver/devel/internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : internal/ceres/CMakeFiles/parameter_block_ordering_test.dir/depend

