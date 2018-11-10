cmake_minimum_required (VERSION 3.0)

project(mpu6050mux)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -DDEBUG=0 -Wall -O3 -g")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

add_executable(mpu main.cpp)

include_directories(${PROJECT_SOURCE_DIR} 
/home/pi/RoboArm/Standalones/Multiplexer/
/home/pi/RoboArm/Standalones/MPU6050/
)

find_library(MUX_LIB multiplexer HINTS /home/pi/RoboArm/Standalones/Multiplexer/${CMAKE_BUILD_TYPE}/lib/)
find_library(MPU6050_LIB mpu6050 HINTS /home/pi/RoboArm/Standalones/MPU6050/${CMAKE_BUILD_TYPE}/lib/)
target_link_libraries(mpu ${MPU6050_LIB} ${MUX_LIB} bcm2835 wiringPi pthread m)

#set(CMAKE_BUILD_DIRECTORY ../build)

set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
#set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)
