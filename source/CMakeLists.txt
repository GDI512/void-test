# =============================================================================
#   Source directory CMakeLists.txt file
#   The void-test library target and everything related to its use outside
#   this project (installing, packaging, exports etc.) should be put here
# =============================================================================

cmake_minimum_required (VERSION 3.17)

set (CMAKE_SRCDIR ${PROJECT_SOURCE_DIR}/cmake)
set (CMAKE_OUTDIR ${PROJECT_BINARY_DIR}/cmake)

file (GLOB HEADER_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file (GLOB SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library (void-test STATIC)

if (NOT ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    add_library (void-test::void-test ALIAS void-test)
endif ()

target_sources (void-test PRIVATE ${SOURCE_FILES})

target_compile_features (void-test PUBLIC cxx_std_17)

target_include_directories (void-test PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install (
    TARGETS void-test
    EXPORT void-test-targets
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install (FILES ${HEADER_FILES} DESTINATION include)

install (EXPORT void-test-targets
    FILE void-test-targets.cmake
    NAMESPACE void-test::
    DESTINATION cmake
)

configure_package_config_file (
    ${CMAKE_SRCDIR}/Config.cmake
    ${CMAKE_OUTDIR}/void-test-config.cmake
    INSTALL_DESTINATION cmake
)

write_basic_package_version_file (
    ${CMAKE_OUTDIR}/void-test-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

set (CONFIG_FILES
    ${CMAKE_OUTDIR}/void-test-config.cmake
    ${CMAKE_OUTDIR}/void-test-config-version.cmake
)

install (FILES ${CONFIG_FILES} DESTINATION cmake)
