# =============================================================================
#   CMake module for global compiler flags
# =============================================================================

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options (/W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    add_compile_options (-Wall -Wextra -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_compile_options (-Wall -Wextra -pedantic -march=native)
endif ()