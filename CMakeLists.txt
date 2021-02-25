cmake_minimum_required (VERSION 3.15)

project (cppltf VERSION 0.1.0 LANGUAGES CXX)

enable_testing ()

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_subdirectory (source)
    add_subdirectory (test)
else ()
    add_subdirectory (source)
endif ()
