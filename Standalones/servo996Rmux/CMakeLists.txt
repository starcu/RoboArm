cmake_minimum_required (VERSION 3.0)

project(servo996mux)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -DDEBUG=0 -Wall -O3 -g")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

#set(target_src)
#set(target_headers)

add_executable(servo main.cpp)
include_directories(${PROJECT_SOURCE_DIR} /home/pi/RoboArm/Standalones/Multiplexer/)
find_library(MUX_LIB multiplexer HINTS /home/pi/RoboArm/Standalones/Multiplexer/build/lib/)
target_link_libraries(servo PUBLIC ${MUX_LIB} bcm2835 wiringPi pthread m)

set(CMAKE_BUILD_DIRECTORY ../build)
