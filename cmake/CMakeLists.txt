cmake_minimum_required(VERSION 2.8.8)

set(target "vpxenc")

project(${target})

# Add directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(cmake/Compiler.cmake REQUIRED)

find_package(OpenCV REQUIRED)

file(GLOB srcs "src/*.cpp")
file(GLOB hdrs "src/*.hpp")

add_executable( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${OpenCV_LIBS} )


