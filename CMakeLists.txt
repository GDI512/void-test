# =============================================================================
#   Main CMakeLists.txt file. Command line for clang-tidy, global compiler
#   options, CMake modules and cache variables should be put here.
# =============================================================================

cmake_minimum_required (VERSION 3.17)

project (void-test LANGUAGES CXX)

include (CTest)

set (VOID_TEST_TARGET void-test)
set (VOID_TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_CLANG_TIDY clang-tidy)

if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options (-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_compile_options (-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options (/W4)
endif ()

add_subdirectory (source)
add_subdirectory (test)
add_subdirectory (example)
