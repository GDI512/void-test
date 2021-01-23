# =============================================================================
#   Source directory CMakeLists.txt file
#   The void-test library target and everything related to its use outside
#   this project (installing, packaging, exports etc.) should be put here
# =============================================================================

cmake_minimum_required (VERSION 3.15)

add_library (voidtest STATIC)
target_sources (voidtest PRIVATE main.cpp output.cpp state.cpp type.cpp)
target_include_directories (voidtest PUBLIC ../include)
target_compile_features (voidtest PUBLIC cxx_std_17)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options (voidtest PRIVATE -Werror -Wall -Wextra)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options (voidtest PRIVATE -Werror -Wall -Wextra)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options (voidtest PRIVATE /permissive- /WX /W4)
endif ()

if (NOT ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    add_library (voidtest::voidtest ALIAS voidtest)
endif ()
