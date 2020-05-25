file(GLOB_RECURSE _sources ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
add_executable(libdaylight-tests ${_sources})

target_link_libraries(libdaylight-tests PRIVATE libdaylight)

enable_testing()
add_test(NAME libdaylight COMMAND libdaylight-tests)
