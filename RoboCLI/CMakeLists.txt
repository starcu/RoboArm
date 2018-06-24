cmake_minimum_required (VERSION 3.0)

project("RoboCLI")

include_directories(
					${PROJECT_SOURCE_DIR}/include/
					${CMAKE_SOURCE_DIR}/SimpleSocketServer/
					)

add_executable(RoboCLI src/RoboCLIMain.cpp src/RoboCLI.cpp)

target_link_libraries(RoboCLI simplesocketclient) 

set(CMAKE_BUILD_DIRECTORY ../build)