cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(
  daylight_pydoc
)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME daylight
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../pybind
)

# ---- Setup targets ----

get_filename_component(DAYLIGHT_ROOT ../ ABSOLUTE)
set(PYTHONPATH "${DAYLIGHT_ROOT}" "${CMAKE_BINARY_DIR}/_deps/daylight-build")

if (NOT DEFINED MSVC)
    string(REPLACE ";" ":" PYTHONPATH "${PYTHONPATH}")
endif()

add_custom_target(
    pydocs
    ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH}" make html
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
)
add_dependencies(pydocs daylight)

add_custom_target(
    pydoctest
    ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH}" make doctest
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
)
add_dependencies(pydoctest daylight)
