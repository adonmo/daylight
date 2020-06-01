file(GLOB_RECURSE _sources ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(libdaylight_c ${_sources})
set_target_properties(libdaylight_c PROPERTIES PREFIX "")
set_target_properties(libdaylight_c PROPERTIES SUFFIX "-${LIBDAYLIGHT_VERSION}.so")
target_link_libraries(libdaylight_c PRIVATE libdaylight)
