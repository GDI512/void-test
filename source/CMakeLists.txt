cmake_minimum_required (VERSION 3.15)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (HEADER_DIR ${PROJECT_SOURCE_DIR}/include)

file (GLOB SOURCE CONFIGURE_DEPENDS ${SOURCE_DIR}/*.cpp)
file (GLOB HEADER CONFIGURE_DEPENDS ${HEADER_DIR}/*.hpp)

add_library (cppltf STATIC)
target_sources (cppltf PRIVATE ${SOURCE})
target_include_directories (cppltf PUBLIC ${HEADER_DIR})
target_compile_features (cppltf PUBLIC cxx_std_17)

if (NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    add_library (cppltf::cppltf ALIAS cppltf)
endif ()
