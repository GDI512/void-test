cmake_minimum_required (VERSION 3.15)

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set (HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

file (GLOB SOURCE CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cpp")
file (GLOB HEADER CONFIGURE_DEPENDS "${HEADER_DIR}/*.hpp")

find_program (CLANG_TIDY clang-tidy)
find_program (CLANG_FORMAT clang-format)

if (CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

add_library (cppltf STATIC)
target_sources (cppltf PRIVATE ${SOURCE})
target_include_directories (cppltf PUBLIC ${HEADER_DIR})
target_compile_features (cppltf PUBLIC cxx_std_17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options (cppltf PRIVATE -Werror -Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options (cppltf PRIVATE -Werror -Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options (cppltf PRIVATE /permissive- /WX /W4)
endif ()

if (NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_library (cppltf::cppltf ALIAS cppltf)
endif ()

if (CLANG_FORMAT)
    foreach (FILE IN LISTS SOURCE HEADER)
        execute_process (COMMAND clang-format -i ${FILE})
    endforeach ()
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
