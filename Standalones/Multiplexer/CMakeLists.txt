cmake_minimum_required (VERSION 3.0)

project(Multiplexer)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -DDEBUG=0 -Wall -g -O3")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

add_executable(mux main.cpp)
add_library(multiplexer Multiplexer.cpp Multiplexer.h)

target_link_libraries(multiplexer bcm2835 wiringPi m pthread)
target_link_libraries(mux bcm2835 wiringPi m pthread multiplexer)

set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ../build/bin)
set(LIBRARY_OUTPUT_PATH ../build/lib)
