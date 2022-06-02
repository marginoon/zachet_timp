cmake_minimum_required(VERSION 3.21)

SET(COVERAGE OFF CACHE BOOL "Coverage")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(Testik)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest" "gtest")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/banking)
add_executable(Test ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)

if (COVERAGE)
    target_compile_options(Test PRIVATE --coverage)
    target_link_libraries(Test PRIVATE --coverage)
endif()

target_include_directories(Test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)
target_link_libraries(Test PRIVATE banking gtest gtest_main gmock_main)
