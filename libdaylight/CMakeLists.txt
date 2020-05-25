file(GLOB_RECURSE _sources ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(libdaylight ${_sources})
set_target_properties(libdaylight PROPERTIES PREFIX "")
set_target_properties(libdaylight PROPERTIES SUFFIX "-${LIBDAYLIGHT_VERSION}.so")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

target_include_directories(libdaylight PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
