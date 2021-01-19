# =============================================================================
#   Top-level CMakeLists.txt file
#   Subdirectories and modules should be included only in this file
# =============================================================================

cmake_minimum_required (VERSION 3.15)

project (void-test VERSION 0.1.0 LANGUAGES CXX)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include (CTest)

find_program (CLANG_TIDY clang-tidy)

set (TEST_OUTDIR ${PROJECT_BINARY_DIR}/bin/test)
set (LIBRARY_OUTDIR ${PROJECT_BINARY_DIR}/lib)

if (CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    add_subdirectory (source ${LIBRARY_OUTDIR})
    if (BUILD_TESTING)
        add_subdirectory (test ${TEST_OUTDIR})
    endif ()
else ()
    add_subdirectory (source ${LIBRARY_OUTDIR})
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
