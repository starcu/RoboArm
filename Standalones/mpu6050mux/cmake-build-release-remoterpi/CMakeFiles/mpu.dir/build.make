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
CMAKE_SOURCE_DIR = /home/pi/RoboArm/Standalones/mpu6050mux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi

# Include any dependencies generated for this target.
include CMakeFiles/mpu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mpu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mpu.dir/flags.make

CMakeFiles/mpu.dir/main.cpp.o: CMakeFiles/mpu.dir/flags.make
CMakeFiles/mpu.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mpu.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpu.dir/main.cpp.o -c /home/pi/RoboArm/Standalones/mpu6050mux/main.cpp

CMakeFiles/mpu.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpu.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/RoboArm/Standalones/mpu6050mux/main.cpp > CMakeFiles/mpu.dir/main.cpp.i

CMakeFiles/mpu.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpu.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/RoboArm/Standalones/mpu6050mux/main.cpp -o CMakeFiles/mpu.dir/main.cpp.s

CMakeFiles/mpu.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mpu.dir/main.cpp.o.requires

CMakeFiles/mpu.dir/main.cpp.o.provides: CMakeFiles/mpu.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpu.dir/build.make CMakeFiles/mpu.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mpu.dir/main.cpp.o.provides

CMakeFiles/mpu.dir/main.cpp.o.provides.build: CMakeFiles/mpu.dir/main.cpp.o


CMakeFiles/mpu.dir/I2Cdev.cpp.o: CMakeFiles/mpu.dir/flags.make
CMakeFiles/mpu.dir/I2Cdev.cpp.o: ../I2Cdev.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mpu.dir/I2Cdev.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpu.dir/I2Cdev.cpp.o -c /home/pi/RoboArm/Standalones/mpu6050mux/I2Cdev.cpp

CMakeFiles/mpu.dir/I2Cdev.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpu.dir/I2Cdev.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/RoboArm/Standalones/mpu6050mux/I2Cdev.cpp > CMakeFiles/mpu.dir/I2Cdev.cpp.i

CMakeFiles/mpu.dir/I2Cdev.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpu.dir/I2Cdev.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/RoboArm/Standalones/mpu6050mux/I2Cdev.cpp -o CMakeFiles/mpu.dir/I2Cdev.cpp.s

CMakeFiles/mpu.dir/I2Cdev.cpp.o.requires:

.PHONY : CMakeFiles/mpu.dir/I2Cdev.cpp.o.requires

CMakeFiles/mpu.dir/I2Cdev.cpp.o.provides: CMakeFiles/mpu.dir/I2Cdev.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpu.dir/build.make CMakeFiles/mpu.dir/I2Cdev.cpp.o.provides.build
.PHONY : CMakeFiles/mpu.dir/I2Cdev.cpp.o.provides

CMakeFiles/mpu.dir/I2Cdev.cpp.o.provides.build: CMakeFiles/mpu.dir/I2Cdev.cpp.o


CMakeFiles/mpu.dir/MPU6050.cpp.o: CMakeFiles/mpu.dir/flags.make
CMakeFiles/mpu.dir/MPU6050.cpp.o: ../MPU6050.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mpu.dir/MPU6050.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpu.dir/MPU6050.cpp.o -c /home/pi/RoboArm/Standalones/mpu6050mux/MPU6050.cpp

CMakeFiles/mpu.dir/MPU6050.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpu.dir/MPU6050.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/RoboArm/Standalones/mpu6050mux/MPU6050.cpp > CMakeFiles/mpu.dir/MPU6050.cpp.i

CMakeFiles/mpu.dir/MPU6050.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpu.dir/MPU6050.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/RoboArm/Standalones/mpu6050mux/MPU6050.cpp -o CMakeFiles/mpu.dir/MPU6050.cpp.s

CMakeFiles/mpu.dir/MPU6050.cpp.o.requires:

.PHONY : CMakeFiles/mpu.dir/MPU6050.cpp.o.requires

CMakeFiles/mpu.dir/MPU6050.cpp.o.provides: CMakeFiles/mpu.dir/MPU6050.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpu.dir/build.make CMakeFiles/mpu.dir/MPU6050.cpp.o.provides.build
.PHONY : CMakeFiles/mpu.dir/MPU6050.cpp.o.provides

CMakeFiles/mpu.dir/MPU6050.cpp.o.provides.build: CMakeFiles/mpu.dir/MPU6050.cpp.o


# Object files for target mpu
mpu_OBJECTS = \
"CMakeFiles/mpu.dir/main.cpp.o" \
"CMakeFiles/mpu.dir/I2Cdev.cpp.o" \
"CMakeFiles/mpu.dir/MPU6050.cpp.o"

# External object files for target mpu
mpu_EXTERNAL_OBJECTS =

../Release/bin/mpu: CMakeFiles/mpu.dir/main.cpp.o
../Release/bin/mpu: CMakeFiles/mpu.dir/I2Cdev.cpp.o
../Release/bin/mpu: CMakeFiles/mpu.dir/MPU6050.cpp.o
../Release/bin/mpu: CMakeFiles/mpu.dir/build.make
../Release/bin/mpu: /home/pi/RoboArm/Standalones/Multiplexer/Release/lib/libmultiplexer.a
../Release/bin/mpu: CMakeFiles/mpu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../Release/bin/mpu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mpu.dir/build: ../Release/bin/mpu

.PHONY : CMakeFiles/mpu.dir/build

CMakeFiles/mpu.dir/requires: CMakeFiles/mpu.dir/main.cpp.o.requires
CMakeFiles/mpu.dir/requires: CMakeFiles/mpu.dir/I2Cdev.cpp.o.requires
CMakeFiles/mpu.dir/requires: CMakeFiles/mpu.dir/MPU6050.cpp.o.requires

.PHONY : CMakeFiles/mpu.dir/requires

CMakeFiles/mpu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mpu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mpu.dir/clean

CMakeFiles/mpu.dir/depend:
	cd /home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/RoboArm/Standalones/mpu6050mux /home/pi/RoboArm/Standalones/mpu6050mux /home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi /home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi /home/pi/RoboArm/Standalones/mpu6050mux/cmake-build-release-remoterpi/CMakeFiles/mpu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mpu.dir/depend

