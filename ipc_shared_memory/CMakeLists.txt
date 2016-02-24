cmake_minimum_required (VERSION 2.8)
project (ipcSharedMemory)

set(CMAKE_CXX_FLAGS "--std=c++11 -O3  -Werror")

add_library(vectorMatch src/vectorMatch.cpp)
add_library(parser src/parser.cpp)

add_executable(sakfy6_hw2 test/runner.cpp)
target_link_libraries(sakfy6_hw2 parser vectorMatch)

