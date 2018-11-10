cmake_minimum_required (VERSION 3.0)

project(servo996mux)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -Wall -O3 -g")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

#set(target_src)
#set(target_headers)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

add_executable(servo main.cpp)
include_directories(${PROJECT_SOURCE_DIR} /home/pi/RoboArm/Standalones/Multiplexer/ /home/pi/RoboArm/Standalones/ServoCtrl/)
find_library(MUX_LIB multiplexer HINTS /home/pi/RoboArm/Standalones/Multiplexer/${CMAKE_BUILD_TYPE}/lib/)
find_library(SERVO_LIB servo HINTS /home/pi/RoboArm/Standalones/ServoCtrl/${CMAKE_BUILD_TYPE}/lib/)

target_link_libraries(servo PUBLIC ${MUX_LIB} ${SERVO_LIB} bcm2835 wiringPi pthread m)

#set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
#set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)
