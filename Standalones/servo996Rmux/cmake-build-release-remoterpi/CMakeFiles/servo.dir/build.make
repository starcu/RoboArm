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
CMAKE_SOURCE_DIR = /home/pi/RoboArm/Standalones/servo996Rmux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi

# Include any dependencies generated for this target.
include CMakeFiles/servo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/servo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/servo.dir/flags.make

CMakeFiles/servo.dir/main.cpp.o: CMakeFiles/servo.dir/flags.make
CMakeFiles/servo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/servo.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/servo.dir/main.cpp.o -c /home/pi/RoboArm/Standalones/servo996Rmux/main.cpp

CMakeFiles/servo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/servo.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/RoboArm/Standalones/servo996Rmux/main.cpp > CMakeFiles/servo.dir/main.cpp.i

CMakeFiles/servo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/servo.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/RoboArm/Standalones/servo996Rmux/main.cpp -o CMakeFiles/servo.dir/main.cpp.s

CMakeFiles/servo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/servo.dir/main.cpp.o.requires

CMakeFiles/servo.dir/main.cpp.o.provides: CMakeFiles/servo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/servo.dir/build.make CMakeFiles/servo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/servo.dir/main.cpp.o.provides

CMakeFiles/servo.dir/main.cpp.o.provides.build: CMakeFiles/servo.dir/main.cpp.o


# Object files for target servo
servo_OBJECTS = \
"CMakeFiles/servo.dir/main.cpp.o"

# External object files for target servo
servo_EXTERNAL_OBJECTS =

../Release/bin/servo: CMakeFiles/servo.dir/main.cpp.o
../Release/bin/servo: CMakeFiles/servo.dir/build.make
../Release/bin/servo: /home/pi/RoboArm/Standalones/Multiplexer/Release/lib/libmultiplexer.a
../Release/bin/servo: CMakeFiles/servo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../Release/bin/servo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/servo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/servo.dir/build: ../Release/bin/servo

.PHONY : CMakeFiles/servo.dir/build

CMakeFiles/servo.dir/requires: CMakeFiles/servo.dir/main.cpp.o.requires

.PHONY : CMakeFiles/servo.dir/requires

CMakeFiles/servo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/servo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/servo.dir/clean

CMakeFiles/servo.dir/depend:
	cd /home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/RoboArm/Standalones/servo996Rmux /home/pi/RoboArm/Standalones/servo996Rmux /home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi /home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi /home/pi/RoboArm/Standalones/servo996Rmux/cmake-build-release-remoterpi/CMakeFiles/servo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/servo.dir/depend

