cmake_minimum_required (VERSION 3.0)

project(mpu6050)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -DDEBUG=0 -Wall -O3 -g")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

add_executable(mpu main.cpp)
add_library(mpu6050 I2Cdev.cpp MPU6050.cpp)

target_link_libraries(mpu6050 bcm2835 wiringPi pthread m)
target_link_libraries(mpu mpu6050)

#set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)
