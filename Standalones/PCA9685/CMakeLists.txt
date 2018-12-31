cmake_minimum_required (VERSION 3.0)

project(pca9685)

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

add_executable(pca main.cpp)
add_library(pca9685 I2Cdev.cpp PCA9685.cpp)

target_link_libraries(pca9685 bcm2835 wiringPi pthread m)
target_link_libraries(pca pca9685)

#set(CMAKE_BUILD_DIRECTORY ../build)
#set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
#set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)
