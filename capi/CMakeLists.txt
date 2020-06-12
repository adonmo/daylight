cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(
  daylight_c
  LANGUAGES CXX
)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME libdaylight
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

# ---- Create library ----

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
add_library(daylight_c ${headers} ${sources})
target_link_libraries(daylight_c libdaylight)

set_target_properties(daylight_c PROPERTIES CXX_STANDARD 11)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(daylight_c PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

target_include_directories(daylight_c
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)
