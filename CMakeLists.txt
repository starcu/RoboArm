cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_FLAGS "-std=c++17 -Wall -g -O3 -lpthread")

project (RoboArm)
add_subdirectory(RoboController)
add_subdirectory(RoboCLI)
add_subdirectory(SimpleSocketServer)