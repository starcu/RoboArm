cmake_minimum_required (VERSION 3.0)

project("SimpleSocketServer")

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

add_library(simplesocketserver server.cpp)
add_library(simplesocketclient client.cpp)

set(CMAKE_BUILD_DIRECTORY ../build)