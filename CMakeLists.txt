cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)

project(libdaylight)
include(cmake/WriteVersionInfo.cmake)

if(NOT DEFINED MSVC)
    set(BUILD_SHARED_LIBS ON)
endif()

enable_testing()

add_subdirectory(libdaylight)
add_subdirectory(capi)
add_subdirectory(tests)
add_subdirectory(pybind)
add_subdirectory(docs)
