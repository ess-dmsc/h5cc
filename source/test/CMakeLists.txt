cmake_minimum_required(VERSION 3.1)
project(h5cc_test CXX)

find_package(Threads)
find_package(GTest)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${h5cc_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
)

add_executable(
  ${PROJECT_NAME}
  main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  ${h5cc_LIBRARIES}
  ${GTEST_BOTH_LIBRARIES}
  pthread
  dl
)


