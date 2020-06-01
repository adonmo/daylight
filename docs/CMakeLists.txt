add_custom_target(
    pydocs
    ${CMAKE_COMMAND} -E env PYTHONPATH="${CMAKE_SOURCE_DIR}:${CMAKE_SOURCE_DIR}/build/pybind:${PYTHONATH}" make html
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
add_dependencies(pydocs daylight)
