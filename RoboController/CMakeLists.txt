cmake_minimum_required (VERSION 3.0)

project(RoboController)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -Wall -g -O3")

find_package(Boost REQUIRED)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/) # dir for executables

add_executable(robo src/RoboControllerMain.cpp src/RoboController.cpp src/RoboLogger.cpp)

include_directories( ${mpu6050_INCLUDE_DIRECTORIES} )
include_directories( ${multiplexer_INCLUDE_DIRECTORIES} )
include_directories( ${servo_INCLUDE_DIRECTORIES} )
include_directories( ${simplesocket_INCLUDE_DIRECTORIES} )
include_directories(${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/include
		/home/pi/RoboArm/Standalones/Multiplexer/
		/home/pi/RoboArm/Standalones/ServoCtrl/
		/home/pi/RoboArm/Standalones/MPU6050/
		/home/pi/RoboArm/Standalones/SimpleSocketServer/)

target_link_libraries(robo mpu6050 multiplexer servo simplesocket boost_system boost_thread boost_log boost_log_setup bcm2835 wiringPi m pthread)

#set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/)