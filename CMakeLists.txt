cmake_minimum_required (VERSION 3.15)

project (void_test VERSION 0.1.0 LANGUAGES CXX)

enable_testing ()

find_program (PDFLATEX pdflatex)
find_program (CLANG_TIDY clang-tidy)

if (CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_subdirectory (source)
    add_subdirectory (test)
    if (PDFLATEX)
        add_subdirectory (resource)
    endif ()
else ()
    add_subdirectory (source)
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
