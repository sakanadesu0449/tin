cmake_minimum_required (VERSION 4.0)

project (tin)

set(TAGLIB_ROOT "C:/projects/taglib")

set(TAGLIB_INCLUDE_DIRS "${TAGLIB_ROOT}/include")
set(TAGLIB_LIBRARIES "${TAGLIB_ROOT}/lib/libtag.a")

set (CMAKE_CXX_STANDARD 17)
file (GLOB CODE_SOURCES "*.cpp")

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_executable (tin ${CODE_SOURCES})

target_include_directories(tin PRIVATE ${TAGLIB_INCLUDE_DIRS})
target_link_libraries(tin PRIVATE ${TAGLIB_LIBRARIES})
