cmake_minimum_required (VERSION 3.15)

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set (HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

file (GLOB SOURCE CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cpp")
file (GLOB HEADER CONFIGURE_DEPENDS "${HEADER_DIR}/*.hpp")

add_library (voidtest STATIC)
target_sources (voidtest PRIVATE ${SOURCE})
target_include_directories (voidtest PUBLIC ${HEADER_DIR})
target_compile_features (voidtest PUBLIC cxx_std_17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options (voidtest PRIVATE -Werror -Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options (voidtest PRIVATE -Werror -Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options (voidtest PRIVATE /permissive- /WX /W4)
endif ()

if (NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_library (voidtest::voidtest ALIAS voidtest)
endif ()
