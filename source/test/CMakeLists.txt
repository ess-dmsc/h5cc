cmake_minimum_required(VERSION 3.1)
project(h5cc_test CXX)

# Set C++11 flag.
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Threads)
find_package(GTest)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${H5CC_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
)

add_executable(
  ${PROJECT_NAME}
  main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  ${H5CC_LIBRARIES}
  ${GTEST_BOTH_LIBRARIES}
  pthread
  dl
)


