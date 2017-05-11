# HDF5
set(HDF5_USE_SHARED_LIBRARIES OFF)
FIND_PACKAGE(HDF5 1.8.15 COMPONENTS CXX HL REQUIRED)
add_library(HDF5 INTERFACE IMPORTED)
set_property(TARGET HDF5 PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${HDF5_INCLUDE_DIRS})

set(h5cc_SRC
    H5CC_Common.cpp
    H5CC_DataSet.cpp
    H5CC_File.cpp
    H5CC_Shape.cpp
)

set(h5cc_INC
    H5CC_Common.h
    H5CC_DataSet.h
    H5CC_Enum.h
    H5CC_Exception.h
    H5CC_File.h
    H5CC_Group.h
    H5CC_Location.h
    H5CC_Shape.h
    H5CC_Types.h
    H5CC_DataSet.tpp
    H5CC_Enum.tpp
    H5CC_Group.tpp
    H5CC_Location.tpp
)

set(h5cc_INC_DIR "./")

set(target h5cc)

add_library(
    ${target}
    ${h5cc_SRC}
    ${h5cc_INC}
)

target_include_directories(
    ${target}
    PUBLIC ${h5cc_INC_DIR}
    PUBLIC ${HDF5_INCLUDE_DIRS}
)

target_link_libraries(
    ${target}
    ${HDF5_LIBRARIES}
)

set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
set_target_properties(${target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")

install(TARGETS ${target} DESTINATION lib)
install(FILES ${h5cc_INC} DESTINATION include/h5cc)

if (${test_h5cc})
    include(../test/CMakeLists.txt)
endif()
