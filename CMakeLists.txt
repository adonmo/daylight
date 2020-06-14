cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

project(
  libdaylight
  LANGUAGES CXX
)
# Get version from VERSION file instead of hardcoding here
# This is so that we can maintain a single version across C++ and Python
file(STRINGS VERSION LIBDAYLIGHT_VERSION)
set(PROJECT_VERSION ${LIBDAYLIGHT_VERSION})

message(${LIBDAYLIGHT_VERSION})

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Dependencies ----
# For more info on CPM dependecies, see https://github.com/TheLartians/CPM.cmake

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.3
)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files automatically.
# Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

add_library(libdaylight ${headers} ${sources})

set_target_properties(libdaylight PROPERTIES
    CXX_STANDARD 11
    POSITION_INDEPENDENT_CODE ON
    PREFIX ""
)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(libdaylight PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

target_include_directories(libdaylight
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed
# should match the project's regular header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  DEPENDENCIES ""
)
