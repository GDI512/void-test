# =============================================================================
#   Source directory CMakeLists.txt file.
#   The void_test library target and everything related to its use outside
#   this project (installing, packaging, aliases etc.) should be put here.
# =============================================================================

cmake_minimum_required (VERSION 3.17)

set (source_dir ${PROJECT_SOURCE_DIR}/source)
set (include_dir $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

file (GLOB source_files CONFIGURE_DEPENDS ${source_dir}/*.cpp)
file (GLOB header_files CONFIGURE_DEPENDS ${include_dir}/*.hpp)

add_library (void_test STATIC)
add_library (void_test::void_test ALIAS void_test)
target_sources (void_test PRIVATE ${source_files})
target_include_directories (void_test PUBLIC ${include_dir})
target_compile_features (void_test PUBLIC cxx_std_17)

install (TARGETS void_test
         EXPORT VoidTestTargets
         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install (FILES ${header_files} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install (EXPORT VoidTestTargets
         FILE VoidTestTargets.cmake
         NAMESPACE void_test::
         DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
