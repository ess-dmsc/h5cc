enable_testing()

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

set(unitTest_SRC
    ../test/main.cpp
)

set(unitTest_INC
    ../test/ExceptionUtil.h
)

set(target h5cc_test)
add_executable(
    ${target}
    ${h5cc_SRC}
    ${h5cc_INC}
    ${unitTest_SRC}
    ${unitTest_INC}
)

target_include_directories(
    ${target}
    PRIVATE ${GTEST_INCLUDE_DIRS}
    PRIVATE ${HDF5_INCLUDE_DIRS}
    PRIVATE ${h5cc_INC_DIR}
)

target_link_libraries(
    ${target}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${HDF5_LIBRARIES}
)

set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

add_test(NAME ${target} COMMAND ${target})
