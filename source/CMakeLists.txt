cmake_minimum_required (VERSION 3.15)

file (GLOB SOURCE CONFIGURE_DEPENDS *.cpp)

add_library (voidtest STATIC)
target_sources (voidtest PRIVATE ${SOURCE})
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
