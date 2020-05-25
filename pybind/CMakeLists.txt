file(GLOB_RECURSE _sources ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

find_package(pybind11)
pybind11_add_module(daylight "${_sources}")

target_link_libraries(daylight PRIVATE libdaylight)
set_target_properties(daylight PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                        SUFFIX "${PYTHON_MODULE_EXTENSION}")
