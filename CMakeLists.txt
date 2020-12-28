cmake_minimum_required (VERSION 3.17)

project (VoidTest LANGUAGES CXX)

option (TESTS "Build tests")
option (EXAMPLES "Build examples")
option (LINT "Set CMake to run clang-tidy")

if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options (-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_compile_options (-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options (/W4)
endif ()

add_subdirectory (source ${CMAKE_CURRENT_BINARY_DIR}/lib)

if (LINT)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

if (TESTS)
    enable_testing ()
    add_subdirectory (test ${CMAKE_CURRENT_BINARY_DIR}/exe/test)
endif ()

if (EXAMPLES)
    add_subdirectory (example ${CMAKE_CURRENT_BINARY_DIR}/exe/example)
endif ()
