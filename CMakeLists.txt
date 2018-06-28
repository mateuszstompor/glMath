cmake_minimum_required(VERSION 3.9)
project(glMath VERSION 1.0.0 DESCRIPTION "math library designed to be used in 3D graphics projects")

add_library(glMath INTERFACE)
target_include_directories(glMath INTERFACE glMath/)