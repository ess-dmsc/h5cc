cmake_minimum_required(VERSION 3.1)
project(H5CCTest CXX)

# Set C++11 flag.
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set(HDF5_USE_STATIC_LIBRARIES ON)
set(HDF5_USE_SHARED_LIBRARIES ON)

find_package(Threads)

FIND_PACKAGE(HDF5 COMPONENTS CXX HL REQUIRED)
FIND_PACKAGE(GTest)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/h5cc
  ${HDF5_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
)

link_directories( ${HDF5_LIBRARY_DIRS} )

file(GLOB sources_H5CC h5cc/*.cpp h5cc/*.h h5cc/*.tpp)
file(GLOB sources_main *.cpp *.h)

set(
  sources_h5cc_test

  ${sources_main}
  ${sources_H5CC}
)

add_executable(h5cc_test ${sources_h5cc_test})

add_library(h5cc ${sources_H5CC})

target_link_libraries(
  h5cc
  ${HDF5_LIBRARIES}
)

target_link_libraries(
  h5cc_test
  ${HDF5_LIBRARIES}
  ${GTEST_BOTH_LIBRARIES}
  pthread
  dl
)


