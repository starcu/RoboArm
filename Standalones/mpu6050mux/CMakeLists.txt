cmake_minimum_required (VERSION 3.0)

project(mpu6050mux)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -DDEBUG=0 -Wall -O3 -g")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

#set(target_src 
#    main.cpp
#    I2Cdev.cpp
#    MPU6050.cpp)

#set(target_headers
#    /home/pi/RoboArm/Standalones/Multiplexer/Multiplexer.h
#    I2Cdev.h
#    MPU6050.h
#    MPU6050_6Axis_MotionApps20.h
#    MPU6050_9Axis_MotionApps41.h
#    helper_3dmath.h)

add_executable(mpu main.cpp I2Cdev.cpp MPU6050.cpp)
include_directories(${PROJECT_SOURCE_DIR} /home/pi/RoboArm/Standalones/Multiplexer/)
find_library(MUX_LIB multiplexer HINTS /home/pi/RoboArm/Standalones/Multiplexer/build/lib/)
target_link_libraries(mpu PUBLIC ${MUX_LIB} bcm2835 wiringPi pthread m)

set(CMAKE_BUILD_DIRECTORY ../build)
