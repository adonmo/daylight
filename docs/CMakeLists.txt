set(PYTHONPATH "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/build/pybind")

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
