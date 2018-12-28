cmake_minimum_required (VERSION 3.0)

project(ServoCtrl)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -Wall -g -O3")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

find_package(Boost REQUIRED)

add_executable(servo_exe main.cpp)
add_library(servo Servo.cpp Servo.h)

target_link_libraries(servo bcm2835 wiringPi m pthread)
target_link_libraries(servo_exe servo)

#set(CMAKE_BUILD_DIRECTORY ../build)
#set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
#set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)

