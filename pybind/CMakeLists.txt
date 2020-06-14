cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(
  daylight
  LANGUAGES CXX
)
# Get version from VERSION file instead of hardcoding here
# This is so that we can maintain a single version across C++ and Python
file(STRINGS ../VERSION DAYLIGHT_VERSION)
set(PROJECT_VERSION ${DAYLIGHT_VERSION})

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME libdaylight
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

CPMAddPackage(
  NAME pybind11
  GITHUB_REPOSITORY pybind/pybind11
  VERSION 2.5.0
)

# ---- Create library ----

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
pybind11_add_module(daylight ${sources})
target_link_libraries(daylight PRIVATE pybind11 libdaylight)
set_target_properties(daylight PROPERTIES
    CXX_STANDARD 11
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(daylight PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

target_include_directories(daylight
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
