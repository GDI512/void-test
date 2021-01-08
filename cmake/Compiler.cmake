# =============================================================================
#   CMake module for global compiler flags
# =============================================================================

set (GCC_WARNINGS
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wuseless-cast
    -Wdouble-promotion
    -Wformat=2
    -Wlifetime
    -pedantic
)

set (CLANG_WARNINGS
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -pedantic
)

set (MSVC_FLAGS
    /permissive-
)

set (MSVC_WARNINGS
    /WX
    /W4
    /w14242
    /w14254
    /w14263
    /w14265
    /w14287
    /we4289
    /w14296
    /w14311
    /w14545
    /w14546
    /w14547
    /w14549
    /w14555
    /w14619
    /w14640
    /w14826
    /w14905
    /w14906
    /w14928
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options (${MSVC_FLAGS} ${MSVC_WARNINGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options (${CLANG_WARNINGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options (${GCC_WARNINGS})
endif ()
