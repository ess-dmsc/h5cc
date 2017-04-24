cmake_minimum_required(VERSION 2.8)
project(H5CC_and_test CXX)

# Common flags
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(h5cc)
add_subdirectory(test)
