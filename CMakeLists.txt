cmake_minimum_required (VERSION 3.17)

project (container_test LANGUAGES CXX)

set (bin ${CMAKE_CURRENT_BINARY_DIR}/bin)
set (test ${CMAKE_CURRENT_SOURCE_DIR}/test)
set (source ${CMAKE_CURRENT_SOURCE_DIR}/source)
set (include ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing ()

if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options (-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_compile_options (-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options (/W4)
endif ()

set (CMAKE_CXX_CLANG_TIDY clang-tidy)

add_subdirectory (${source} ${bin})
add_subdirectory (${test} ${bin}/test)
