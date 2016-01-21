cmake_minimum_required (VERSION 2.8)
project (HWO)

set(CMAKE_CXX_FLAGS "--std=c++11 -g -Werror")


add_library(parser src/parser.cpp)

add_executable(runner test/runner.cpp)
target_link_libraries(runner parser)

