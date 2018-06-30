cmake_minimum_required(VERSION 3.9)
project(glMath VERSION 1.0.0 DESCRIPTION "math library designed to be used in 3D graphics projects")

add_library(glMath INTERFACE)
include_directories(glMath INTERFACE ${CMAKE_SOURCE_DIR})
install(DIRECTORY glMath
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")