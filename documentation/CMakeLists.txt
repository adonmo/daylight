cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(
  daylight_pydoc
)

get_filename_component(DAYLIGHT_ROOT ../ ABSOLUTE)

# ---- Dependencies ----

include("${DAYLIGHT_ROOT}/cmake/CPM.cmake")

CPMAddPackage(
  NAME daylight
  SOURCE_DIR "${DAYLIGHT_ROOT}/pybind"
)

# ---- Setup targets ----

set(PYTHONPATH "${DAYLIGHT_ROOT}" "${CMAKE_BINARY_DIR}/_deps/daylight-build")

if (NOT DEFINED MSVC)
    string(REPLACE ";" ":" PYTHONPATH "${PYTHONPATH}")
endif()

add_custom_target(
    pydocs
    ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH}" make html
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/python"
)
add_dependencies(pydocs daylight)

add_custom_target(
    pydoctest
    ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH}" make doctest
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/python"
)
add_dependencies(pydoctest daylight)
