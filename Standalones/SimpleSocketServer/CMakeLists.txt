cmake_minimum_required (VERSION 3.0)

project(SimpleSocketServer)


set(CMAKE_CXX_FLAGS_DEBUG "-std=c++0x -DDEBUG=1 -Wall -g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++0x -Wall -g -O3")


file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin) # dir for executables
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib) # dir for libraries

include_directories(
		${PROJECT_SOURCE_DIR}/
		)

add_library(simplesocket server.cpp server.h client.cpp client.h)

add_executable(server server_main.cpp server.h)
target_link_libraries(server simplesocket)

add_executable(client client_main.cpp client h)
target_link_libraries(client simplesocket)

set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/bin)
set(LIBRARY_OUTPUT_PATH ../${CMAKE_BUILD_TYPE}/lib)