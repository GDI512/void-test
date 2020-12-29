# =============================================================================
#   Source directory CMakeLists.txt file. The void-test library target and
#   everything related to its use outside this project (installing, packaging
#   etc.) should be put here.
# =============================================================================

cmake_minimum_required (VERSION 3.17)

set (INCLUDE_DIR ${VOID_TEST_SOURCE_DIR}/include)

set (SOURCE_FILES
     output.cpp
     registry.cpp
     resource.cpp
     scope.cpp
     state.cpp
     utility.cpp
     verifier.cpp)

add_library (${VOID_TEST_TARGET} STATIC)
target_sources (${VOID_TEST_TARGET} PRIVATE ${SOURCE_FILES})
target_include_directories (${VOID_TEST_TARGET} PUBLIC ${INCLUDE_DIR})
target_compile_features (${VOID_TEST_TARGET} PUBLIC cxx_std_17)
