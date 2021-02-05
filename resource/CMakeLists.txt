cmake_minimum_required (VERSION 3.15)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set (BUILD_PDF pdflatex -output-directory=${BINARY_DIR} documentation.tex)

add_custom_target (documentation
    ALL
    COMMAND ${BUILD_PDF}
    WORKING_DIRECTORY ${SOURCE_DIR}
)

