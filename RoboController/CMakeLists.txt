cmake_minimum_required (VERSION 3.0)

project("RoboController")

include_directories(
		${PROJECT_SOURCE_DIR}/include/
		${CMAKE_SOURCE_DIR}/SimpleSocketServer/
		)

add_executable(RoboController src/RoboControllerMain.cpp src/RoboController.cpp)

target_link_libraries(RoboController simplesocketserver) 

set(CMAKE_BUILD_DIRECTORY ../build)