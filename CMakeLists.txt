cmake_minimum_required(VERSION 3.9)
project(glMath VERSION 1.0.0 DESCRIPTION "a math library designed to be used in 3D graphics projects")
set(CMAKE_CXX_STANDARD 17)

# Prepare glMath library

add_library(glMath INTERFACE)
install(DIRECTORY glMath
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")

#
# glMath tests
#

IF (BUILD_TESTING)
    find_package(GTest REQUIRED Threads REQUIRED)
    include_directories(glMath)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -g")
    include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
    add_executable(glMath_tests ${CMAKE_SOURCE_DIR}/tests/main.cpp)
    target_sources(glMath_tests PRIVATE tests)
    target_link_libraries(glMath_tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} glMath)
ENDIF(BUILD_TESTING)
