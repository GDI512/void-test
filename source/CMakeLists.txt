# =============================================================================
#   Source directory CMakeLists.txt file
#   The void-test library target and everything related to its use outside
#   this project (installing, packaging, exports etc.) should be put here
# =============================================================================

cmake_minimum_required (VERSION 3.17)

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set (SOURCE_FILES
    main.cpp
    output.cpp
    state.cpp
    type.cpp
    utility.cpp
)

add_library (void-test STATIC)
target_sources (void-test PRIVATE ${SOURCE_FILES})
target_include_directories (void-test PUBLIC ${INCLUDE_DIR})
target_compile_features (void-test PUBLIC cxx_std_17)
set_target_properties (void-test PROPERTIES OUTPUT_NAME voidtest)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options (void-test PRIVATE ${CLANG_FLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options (void-test PRIVATE ${GNU_FLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options (void-test PRIVATE ${MSVC_FLAGS})
endif ()

if (NOT ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    add_library (void-test::void-test ALIAS void-test)
endif ()
