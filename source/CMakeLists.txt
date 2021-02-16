cmake_minimum_required (VERSION 3.15)

if (CLANG_TIDY)
    set (CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

file (GLOB SOURCE CONFIGURE_DEPENDS *.cpp)
file (GLOB HEADER CONFIGURE_DEPENDS ../include/*.hpp)

if (CLANG_FORMAT)
    foreach (FILE IN LISTS SOURCE HEADER)
        execute_process (COMMAND clang-format -i ${FILE})
    endforeach ()
endif ()

add_library (void_test STATIC)
target_sources (void_test PRIVATE ${SOURCE})
target_include_directories (void_test PUBLIC ../include)
target_compile_features (void_test PUBLIC cxx_std_17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options (void_test PRIVATE -Werror -Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options (void_test PRIVATE -Werror -Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options (void_test PRIVATE /permissive- /WX /W4)
endif ()

if (NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_library (void_test::void_test ALIAS void_test)
endif ()

unset (CMAKE_CXX_CLANG_TIDY)
