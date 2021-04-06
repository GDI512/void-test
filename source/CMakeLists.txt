cmake_minimum_required (VERSION 3.15)

add_library (cppltf STATIC)
target_sources (cppltf PRIVATE main.cpp object.cpp output.cpp state.cpp)
target_include_directories (cppltf PRIVATE ../include/)
target_include_directories (cppltf PUBLIC ../include/public/)
target_compile_features (cppltf PUBLIC cxx_std_17)

if (NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_library (cppltf::cppltf ALIAS cppltf)
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options (cppltf PRIVATE -Werror -Wall -Wextra -pedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options (cppltf PRIVATE -Werror -Wall -Wextra -pedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options (cppltf PRIVATE /permissive- /WX /W4)
endif ()
