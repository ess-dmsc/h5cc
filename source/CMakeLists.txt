cmake_minimum_required(VERSION 2.8)
project(H5CCTest CXX)

# Set C++11 flag.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type")

find_package(HDF5 COMPONENTS CXX REQUIRED)

include_directories(h5cc ${HDF5_INCLUDE_DIR})

add_executable(
    h5cc_test 
    
    main.cpp 
    ExceptionUtil.h
    h5cc/H5CC_Common.cpp
    h5cc/H5CC_Types.h
    h5cc/H5CC_DataSet.cpp
    h5cc/H5CC_DataSet.h
    h5cc/H5CC_DataSet.tpp
    h5cc/H5CC_Exception.h
    h5cc/H5CC_File.cpp
    h5cc/H5CC_File.h
    h5cc/H5CC_Group.h
    h5cc/H5CC_Group.tpp
    h5cc/H5CC_Location.h
    h5cc/H5CC_Location.tpp
    h5cc/H5CC_Space.cpp
    h5cc/H5CC_Space.h
)

target_link_libraries(h5cc_test ${HDF5_LIBRARIES})