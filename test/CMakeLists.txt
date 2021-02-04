cmake_minimum_required (VERSION 3.15)

add_library (common OBJECT)
target_sources (common PRIVATE common.cpp)
target_link_libraries (common PUBLIC void_test)

function (add_test_executable target source)
  add_executable (${target})
  target_sources (${target} PRIVATE ${source})
  target_link_libraries (${target} PRIVATE common)
  add_test (NAME ${target} COMMAND ${target})
endfunction ()

add_test_executable (assert assert.cpp)
add_test_executable (generator generator.cpp)
add_test_executable (state state.cpp)
add_test_executable (type type.cpp)
add_test_executable (unit unit.cpp)
add_test_executable (utility utility.cpp)
