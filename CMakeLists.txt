cmake_minimum_required(VERSION 2.8.9)


set(target "mlib" )

project( ${target} )

# Add directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(cmake/Compiler.cmake REQUIRED)

include_directories("include")

find_package(OpenCV REQUIRED)

file(GLOB srcs "src/*.cpp")
file(GLOB hdrs "include/mlib/*.hpp")

add_library( ${target} ${srcs} ${hdrs} )

target_link_libraries( ${target} ${OpenCV_LIBS} )


set(BUILD_EXAMPLES ON CACHE BOOL "Build all examples")

if(BUILD_EXAMPLES)

    file(GLOB examples_list "examples/*.cpp")

    FOREACH(ex ${examples_list})
        string(REGEX REPLACE "^.*/(.+).cpp" "\\1" ex_name ${ex})
        add_executable( ${ex_name} ${ex} )
        target_link_libraries( ${ex_name} "mlib" )
    ENDFOREACH()

endif()
