cmake_minimum_required (VERSION 3.17)

function (add_test_executable target source)
    add_executable (${target})
    target_sources (${target} PRIVATE ${source})
    target_link_libraries (${target} PRIVATE void_test)
    add_test (NAME ${target}_test COMMAND ${target})
endfunction ()

add_test_executable (unit unit.cpp)
add_test_executable (state state.cpp)
add_test_executable (resource resource.cpp)
