# =============================================================================
#   Example directory CMakeLists.txt file. Working code examples, sandbox
#   code for debugging and other stuff should go here.
# =============================================================================

cmake_minimum_required (VERSION 3.17)

function (add_example_executable target source)
    add_executable (${target})
    target_sources (${target} PRIVATE ${source})
    target_link_libraries (${target} PRIVATE ${VOID_TEST_TARGET})
endfunction ()

add_example_executable (vector vector.cpp)
