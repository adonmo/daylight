cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(
  libdaylight-tests
  LANGUAGES CXX
)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 2.12.2
)

if (TEST_INSTALLED_VERSION)
  find_package(libdaylight REQUIRED)
  find_package(daylight REQUIRED)
else()
  CPMAddPackage(
    NAME libdaylight
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
  CPMAddPackage(
    NAME daylight
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../pybind
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.3
)

# ---- Create binary ----

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
add_executable(libdaylight-tests ${sources})
target_link_libraries(libdaylight-tests Catch2 libdaylight)

set_target_properties(libdaylight-tests PROPERTIES CXX_STANDARD 11)

# enable compiler warnings
if (NOT TEST_INSTALLED_VERSION)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(libdaylight PUBLIC -Wall -pedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(libdaylight PUBLIC /W4 /WX)
    target_compile_definitions(libdaylight-tests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add libdaylight-tests ----

ENABLE_TESTING()

add_test(NAME libdaylight COMMAND libdaylight-tests)

# ---- code coverage ----

if (ENABLE_TEST_COVERAGE)
  target_compile_options(libdaylight PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(libdaylight PUBLIC -fprofile-arcs -ftest-coverage)
endif()
