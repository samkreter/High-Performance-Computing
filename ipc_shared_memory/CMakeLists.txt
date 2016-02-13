cmake_minimum_required (VERSION 2.8)
project (ipcSharedMemory)

set(CMAKE_CXX_FLAGS "--std=c++11 -g -Werror")

add_library(vectorMatch src/vectorMatch.cpp)
add_library(parser src/parser.cpp)

add_executable(runner test/runner.cpp)
target_link_libraries(runner parser parser)

