cmake_minimum_required (VERSION 2.8)
project (threadVectorCompare)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    MESSAGE(STATUS "Building with gcc-4.9 since your using a mac and that makes things hard")
    set(CMAKE_CXX_COMPILER "g++-4.9")
ENDIF()


IF(${CMAKE_SYSTEM_NAME} MATCHES "linux")
    MESSAGE(STATUS "Good choice in operating system Sr. continue doing what your doing")
ENDIF()


find_package(OpenMP)
IF(OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
ENDIF()

set(CMAKE_CXX_FLAGS "--std=c++11 -O2 -pthread -D POSITION=$(pos) -Werror")

add_library(vectorMatch src/vectorMatch.cpp)
add_library(parser src/parser.cpp)

add_executable(sakfy6_hw3 test/runner.cpp)
target_link_libraries(sakfy6_hw3 parser vectorMatch)

