cmake_minimum_required (VERSION 3.15)

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_library (citrine)
add_library (citrine::citrine ALIAS citrine)
target_sources (citrine PRIVATE main.cpp state.cpp type.cpp)
target_include_directories (citrine PUBLIC ${INCLUDE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options (citrine PRIVATE -pedantic -Werror -Wall -Wextra -march=native PUBLIC -std=c++20)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options (citrine PRIVATE -pedantic -Werror -Wall -Wextra -march=native PUBLIC -std=c++20)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options (citrine PRIVATE /permissive- /WX /W4 PUBLIC /std:c++latest)
endif ()
