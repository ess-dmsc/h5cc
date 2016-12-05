cmake_minimum_required(VERSION 2.8)
project(H5CCTest CXX)

# Set C++11 flag.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Boost needs this
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_LOG_DYN_LINK")
#find_package(Boost COMPONENTS system REQUIRED)

find_package(HDF5 COMPONENTS CXX REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/h5cc
  ${HDF5_INCLUDE_DIR}
#  ${Boost_INCLUDE_DIR}
)

file(GLOB sources_H5CC h5cc/*.cpp h5cc/*.h h5cc/*.tpp)
file(GLOB sources_main *.cpp *.h)

set(
  sources_h5cc_test

  ${sources_main}
  ${sources_H5CC}
#  ${Boost_LIBRARIES}
)

add_executable(h5cc_test ${sources_h5cc_test})

target_link_libraries(h5cc_test ${HDF5_LIBRARIES})



