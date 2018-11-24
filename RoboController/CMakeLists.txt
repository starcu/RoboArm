cmake_minimum_required (VERSION 3.0)

project(RoboController)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -Wall -g -O3")

find_package(Boost REQUIRED)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/) # dir for executables

add_executable(robo src/RoboControllerMain.cpp src/RoboController.cpp src/RoboLogger.cpp src/KalmanFilter.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/include
		/home/pi/RoboArm/Standalones/Multiplexer/
		/home/pi/RoboArm/Standalones/ServoCtrl/
		/home/pi/RoboArm/Standalones/MPU6050/
		/home/pi/RoboArm/Standalones/SimpleSocketServer/)

find_library(MUX_LIB multiplexer HINTS /home/pi/RoboArm/Standalones/Multiplexer/${CMAKE_BUILD_TYPE}/lib/)
find_library(MPU6050_LIB mpu6050 HINTS /home/pi/RoboArm/Standalones/MPU6050/${CMAKE_BUILD_TYPE}/lib/)
find_library(SERVO_LIB servo HINTS /home/pi/RoboArm/Standalones/ServoCtrl/${CMAKE_BUILD_TYPE}/lib/)
find_library(SOCKET_LIB simplesocket HINTS /home/pi/RoboArm/Standalones/SimpleSocketServer/${CMAKE_BUILD_TYPE}/lib/)
target_link_libraries(robo ${SOCKET_LIB} ${MUX_LIB} ${SERVO_LIB} ${MPU6050_LIB} boost_system boost_thread boost_log boost_log_setup bcm2835 wiringPi m pthread)

#set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/)