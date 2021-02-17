cmake_minimum_required (VERSION 3.15)

project (void_test VERSION 0.1.0 LANGUAGES CXX)

include (CTest)

find_program (PDFLATEX pdflatex)
find_program (CLANG_TIDY clang-tidy)
find_program (CLANG_FORMAT clang-format)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_subdirectory (src)
    add_subdirectory (test)
else ()
    add_subdirectory (src)
endif ()
