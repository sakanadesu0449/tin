cmake_minimum_required (VERSION 4.0)

project (tin)

set (CMAKE_CXX_STANDARD 17)
file (GLOB CODE_SOURCES "*.cpp")

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_executable (tin ${CODE_SOURCES})