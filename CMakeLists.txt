cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -DDEBUG=1 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -g -O3")

project (RoboArm)
add_subdirectory(RoboController)
# add_subdirectory(RoboCLI) # socket based CLI -> TODO

add_subdirectory(Standalones/MPU6050) # position measurement
add_subdirectory(Standalones/PCA9685) # servo control
add_subdirectory(Standalones/Multiplexer) # for MPUs
add_subdirectory(Standalones/SimpleSocketServer) # for CLI


 ### add_subdirectory(Standalones/ServoCtrl)
 ### deprecated -> servo control covered by PCA9685
 ### due to only one HW PWM output in RPi and impossibility of correct control through MUX
 ### software PWMs have too low resolution