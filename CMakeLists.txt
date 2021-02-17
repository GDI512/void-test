cmake_minimum_required (VERSION 3.15)

project (void_test VERSION 0.1.0 LANGUAGES CXX)

include (CTest)
include (CPack)

find_program (PDFLATEX pdflatex)
find_program (CLANG_TIDY clang-tidy)
find_program (CLANG_FORMAT clang-format)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_subdirectory (documentation doc)
    add_subdirectory (source lib)
    add_subdirectory (test bin)
else ()
    add_subdirectory (source lib)
endif ()
