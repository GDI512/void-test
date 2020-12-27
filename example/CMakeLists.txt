cmake_minimum_required (VERSION 3.17)

function (add_example_executable target_name source_file)
    add_executable (${target_name})
    target_sources (${target_name} PRIVATE ${source_file})
    target_link_libraries (${target_name} PRIVATE void_test)
endfunction ()

add_example_executable (vector vector.cpp)
