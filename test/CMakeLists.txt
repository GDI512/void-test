cmake_minimum_required (VERSION 3.17)

function (add_test_executable target_name source_file)
    add_executable (${target_name})
    target_sources (${target_name} PRIVATE ${source_file})
    target_link_libraries (${target_name} PRIVATE void_test)
    add_test (NAME ${target_name}_test COMMAND ${target_name})
endfunction ()

add_test_executable (unit unit.cpp)
add_test_executable (state state.cpp)
