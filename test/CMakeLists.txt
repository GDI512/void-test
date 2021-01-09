# =============================================================================
#   Test directory CMakeLists.txt file
#   All test-related configuration and test targets should go here
# =============================================================================

cmake_minimum_required (VERSION 3.17)

function (add_test_executable target source)
  add_executable (${target})
  target_sources (${target} PRIVATE ${source})
  target_link_libraries (${target} PRIVATE void-test)
  add_test (NAME ${target}_test COMMAND ${target})
endfunction ()

if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    add_test_executable (assert assert.cpp)
    add_test_executable (registry registry.cpp)
    add_test_executable (resource resource.cpp)
    add_test_executable (scope scope.cpp)
    add_test_executable (state state.cpp)
    add_test_executable (verifier verifier.cpp)
endif ()
