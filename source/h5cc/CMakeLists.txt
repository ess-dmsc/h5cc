cmake_minimum_required(VERSION 3.1)
project(H5CC CXX)

# Set C++11 flag.
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#HDF5
#set (HDF5_USE_STATIC_LIBRARIES ON)
set (HDF5_USE_SHARED_LIBRARIES ON)
FIND_PACKAGE (HDF5 COMPONENTS CXX HL REQUIRED)
link_directories ( ${HDF5_LIBRARY_DIRS} )

file(GLOB h5cc_sources *.cpp)
file(GLOB h5cc_headers *.h *.tpp)
foreach (_headerFile ${h5cc_headers})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND h5cc_include_dirs ${_dir})
endforeach()
list(REMOVE_DUPLICATES h5cc_include_dirs)

include_directories(
  ${h5cc_include_dirs}
  ${HDF5_INCLUDE_DIRS}
)

add_library(
  ${PROJECT_NAME}
  ${h5cc_sources}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${HDF5_LIBRARIES}
)

# Expose public includes
set(${PROJECT_NAME}_INCLUDE_DIRS
  ${h5cc_include_dirs}
  ${HDF5_INCLUDE_DIRS}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(${PROJECT_NAME}_LIBRARIES
    -Wl,--whole-archive ${PROJECT_NAME} -Wl,--no-whole-archive
    PARENT_SCOPE)

install(TARGETS H5CC DESTINATION lib)
install(FILES ${h5cc_headers} DESTINATION include/h5cc)
