# =============================================================================
#   Top-level CMakeLists.txt file.
#   Command line for clang-tidy, global compiler options, CMake modules and
#   cache variables should be put here.
# =============================================================================

cmake_minimum_required (VERSION 3.17)

project (void_test LANGUAGES CXX)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include (CTest)
include (GNUInstallDirs)

option (CLANG_TIDY "Run clang-tidy on build")
option (BUILD_EXAMPLES "Build example executables")

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options (/W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options (-Wall -Wextra -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_compile_options (-Wall -Wextra -pedantic -march=native)
endif ()

if (CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

add_subdirectory (source)

if (BUILD_TESTING)
    add_subdirectory (test)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory (example)
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
