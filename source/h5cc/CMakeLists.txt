cmake_minimum_required(VERSION 2.8)
project(h5cc CXX)

# HDF5
#set (HDF5_USE_STATIC_LIBRARIES ON)
set (HDF5_USE_SHARED_LIBRARIES ON)
FIND_PACKAGE (HDF5 COMPONENTS CXX HL REQUIRED)
link_directories ( ${HDF5_LIBRARY_DIRS} )

file(GLOB ${PROJECT_NAME}_sources *.cpp)
file(GLOB ${PROJECT_NAME}_headers *.h *.tpp)
foreach (_headerFile ${${PROJECT_NAME}_headers})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND ${PROJECT_NAME}_include_dirs ${_dir})
endforeach()
list(REMOVE_DUPLICATES ${PROJECT_NAME}_include_dirs)

include_directories(
  ${${PROJECT_NAME}_include_dirs}
  ${HDF5_INCLUDE_DIRS}
)

add_library(
  ${PROJECT_NAME}
  ${${PROJECT_NAME}_sources}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${HDF5_LIBRARIES}
)

# Expose public includes
set(${PROJECT_NAME}_INCLUDE_DIRS
  ${${PROJECT_NAME}_include_dirs}
  ${HDF5_INCLUDE_DIRS}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(${PROJECT_NAME}_LIBRARIES
    ${PROJECT_NAME} ${HDF5_LIBRARIES}
    PARENT_SCOPE)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${${PROJECT_NAME}_headers} DESTINATION
              include/${PROJECT_NAME})
