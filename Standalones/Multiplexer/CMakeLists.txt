cmake_minimum_required (VERSION 3.0)

project(Multiplexer)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -Wall -g -O3")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

find_package(Boost REQUIRED)

add_library(multiplexer Multiplexer.cpp Multiplexer.h)
add_executable(mux main.cpp)
add_executable(test_mux mux_tests.cpp)

target_link_libraries(multiplexer bcm2835 wiringPi m pthread)
target_link_libraries(mux bcm2835 wiringPi m pthread multiplexer)
target_link_libraries(test_mux boost_system boost_unit_test_framework multiplexer)

#set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)

