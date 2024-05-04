cmake_minimum_required(VERSION 3.29.2)

set(MY_PROJECT_NAME "realsense")

project(${MY_PROJECT_NAME} VERSION 0.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(EnableIPOSupport)
include(NoInSourceBuilds)

add_subdirectory(src bin)
add_subdirectory(test)
add_subdirectory(benchmark)
