cmake_minimum_required(VERSION 3.16.2)
set(CMAKE_CXX_STANDARD 11)

project(libdaylight)
include(cmake/WriteVersionInfo.cmake)
set(BUILD_SHARED_LIBS ON)

enable_testing()

add_subdirectory(libdaylight)
add_subdirectory(tests)
add_subdirectory(pybind)
