# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/RoboArm/Standalones/Multiplexer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi

# Include any dependencies generated for this target.
include CMakeFiles/test_mux.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_mux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_mux.dir/flags.make

CMakeFiles/test_mux.dir/mux_tests.cpp.o: CMakeFiles/test_mux.dir/flags.make
CMakeFiles/test_mux.dir/mux_tests.cpp.o: ../mux_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_mux.dir/mux_tests.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_mux.dir/mux_tests.cpp.o -c /home/pi/RoboArm/Standalones/Multiplexer/mux_tests.cpp

CMakeFiles/test_mux.dir/mux_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_mux.dir/mux_tests.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/RoboArm/Standalones/Multiplexer/mux_tests.cpp > CMakeFiles/test_mux.dir/mux_tests.cpp.i

CMakeFiles/test_mux.dir/mux_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_mux.dir/mux_tests.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/RoboArm/Standalones/Multiplexer/mux_tests.cpp -o CMakeFiles/test_mux.dir/mux_tests.cpp.s

CMakeFiles/test_mux.dir/mux_tests.cpp.o.requires:

.PHONY : CMakeFiles/test_mux.dir/mux_tests.cpp.o.requires

CMakeFiles/test_mux.dir/mux_tests.cpp.o.provides: CMakeFiles/test_mux.dir/mux_tests.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_mux.dir/build.make CMakeFiles/test_mux.dir/mux_tests.cpp.o.provides.build
.PHONY : CMakeFiles/test_mux.dir/mux_tests.cpp.o.provides

CMakeFiles/test_mux.dir/mux_tests.cpp.o.provides.build: CMakeFiles/test_mux.dir/mux_tests.cpp.o


# Object files for target test_mux
test_mux_OBJECTS = \
"CMakeFiles/test_mux.dir/mux_tests.cpp.o"

# External object files for target test_mux
test_mux_EXTERNAL_OBJECTS =

../Release/bin/test_mux: CMakeFiles/test_mux.dir/mux_tests.cpp.o
../Release/bin/test_mux: CMakeFiles/test_mux.dir/build.make
../Release/bin/test_mux: ../Release/lib/libmultiplexer.a
../Release/bin/test_mux: CMakeFiles/test_mux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../Release/bin/test_mux"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_mux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_mux.dir/build: ../Release/bin/test_mux

.PHONY : CMakeFiles/test_mux.dir/build

CMakeFiles/test_mux.dir/requires: CMakeFiles/test_mux.dir/mux_tests.cpp.o.requires

.PHONY : CMakeFiles/test_mux.dir/requires

CMakeFiles/test_mux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_mux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_mux.dir/clean

CMakeFiles/test_mux.dir/depend:
	cd /home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/RoboArm/Standalones/Multiplexer /home/pi/RoboArm/Standalones/Multiplexer /home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi /home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi /home/pi/RoboArm/Standalones/Multiplexer/cmake-build-release-remoterpi/CMakeFiles/test_mux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_mux.dir/depend

