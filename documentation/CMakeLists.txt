cmake_minimum_required (VERSION 3.15)

set (SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set (OUTPUT_DIR "${PROJECT_SOURCE_DIR}/build/doc")
set (COMMAND pdflatex -output-directory=${OUTPUT_DIR} document.tex)

if (PDFLATEX)
    execute_process (COMMAND ${COMMAND} WORKING_DIRECTORY ${SOURCE_DIR})
    execute_process (COMMAND ${COMMAND} WORKING_DIRECTORY ${SOURCE_DIR})
endif ()
