cmake_minimum_required(VERSION 3.10)
project(libdaylight)
include(cmake/WriteVersionInfo.cmake)
SET(BUILD_SHARED_LIBS ON)

enable_testing()

add_subdirectory(libdaylight)
add_subdirectory(tests)
add_subdirectory(pybind)
