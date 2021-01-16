# =============================================================================
#   Top-level CMakeLists.txt file
#   Subdirectories and modules should be included only in this file
# =============================================================================

cmake_minimum_required (VERSION 3.17)

project (void-test VERSION 0.1.0 LANGUAGES CXX)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include (CTest)
include (CMakePackageConfigHelpers)
include (Cache)
include (Compiler)

set (TEST_OUTDIR ${PROJECT_BINARY_DIR}/bin/test)
set (SOURCE_OUTDIR ${PROJECT_BINARY_DIR}/lib)

if (VOID_TEST_CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    add_subdirectory (source ${SOURCE_OUTDIR})
    add_subdirectory (test ${TEST_OUTDIR})
else ()
    add_subdirectory (source ${SOURCE_OUTDIR})
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
