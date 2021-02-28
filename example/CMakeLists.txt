cmake_minimum_required (VERSION 3.15)

function (add_example_executable target source)
    add_executable (${target})
    target_sources (${target} PRIVATE ${source})
    target_link_libraries (${target} PRIVATE cppltf)
endfunction ()

add_example_executable (group group.cpp)
add_example_executable (check check.cpp)
