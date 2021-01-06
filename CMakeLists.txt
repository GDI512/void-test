# =============================================================================
#   Top-level CMakeLists.txt file
#   Subdirectories and modules should be included only in this file
# =============================================================================

cmake_minimum_required (VERSION 3.17)

project (void-test VERSION 0.1.0 LANGUAGES CXX)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include (CTest)
include (GNUInstallDirs)
include (CMakePackageConfigHelpers)
include (Cache)
include (Compiler)

set (LIB_OUTDIR ${PROJECT_BINARY_DIR}/lib)
set (TEST_OUTDIR ${PROJECT_BINARY_DIR}/bin/test)

if (CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

add_subdirectory (src ${LIB_OUTDIR})

if (BUILD_TESTING)
    add_subdirectory (test ${TEST_OUTDIR})
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
