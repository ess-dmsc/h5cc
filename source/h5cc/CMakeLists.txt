cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(h5cc CXX)
option(h5noversioncheck "Do not check hdf5 version" OFF)

# HDF5
set(HDF5_USE_SHARED_LIBRARIES ON)
if (h5noversioncheck)
  FIND_PACKAGE(HDF5 COMPONENTS CXX HL REQUIRED)
else()
  FIND_PACKAGE(HDF5 1.8.15 COMPONENTS CXX HL REQUIRED)
endif()
add_library(HDF5 INTERFACE IMPORTED)
set_property(TARGET HDF5 PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${HDF5_INCLUDE_DIRS})
#link_directories ( ${HDF5_LIBRARY_DIRS} )

file(GLOB ${PROJECT_NAME}_sources *.cpp)
file(GLOB ${PROJECT_NAME}_headers *.h *.tpp)
dirs_of(${PROJECT_NAME}_include_dirs "${${PROJECT_NAME}_headers}")

#message(STATUS "sources   " ${${PROJECT_NAME}_sources})
#message(STATUS "headers   " ${${PROJECT_NAME}_headers})
#message(STATUS "inc dir   " ${${PROJECT_NAME}_include_dirs})

add_library(
  ${PROJECT_NAME}
  ${${PROJECT_NAME}_sources}
  ${${PROJECT_NAME}_headers}
)

# shared libraries need PIC
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${${PROJECT_NAME}_include_dirs}
  PUBLIC ${HDF5_INCLUDE_DIRS}
  )

target_link_libraries(
  ${PROJECT_NAME}
  ${HDF5_LIBRARIES}
)

set(${PROJECT_NAME}_LIBRARIES
    ${PROJECT_NAME}
    PARENT_SCOPE)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${${PROJECT_NAME}_headers} DESTINATION
              include/${PROJECT_NAME})
