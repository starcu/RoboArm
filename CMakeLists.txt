cmake_minimum_required (VERSION 3.0)

project (RoboArm)
add_subdirectory(RoboController)
# add_subdirectory(RoboCLI)

add_subdirectory(Standalones/MPU6050)
add_subdirectory(Standalones/Multiplexer)
add_subdirectory(Standalones/ServoCtrl)
add_subdirectory(Standalones/SimpleSocketServer)
