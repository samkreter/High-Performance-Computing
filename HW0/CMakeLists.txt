cmake_minimum_required (VERSION 2.8)
project (HWO)

set(CMAKE_CXX_FLAGS "--std=c++11 -g -Werror")


add_library(swap_algorithms src/page_swap.cpp src/LRU.cpp src/ALRU.cpp)

add_executable(runner test/runner.cpp)
target_link_libraries(runner swap_algorithms)

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -O3")
add_executable(page_generator src/page_generator.cpp)