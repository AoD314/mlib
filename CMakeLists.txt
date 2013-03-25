cmake_minimum_required(VERSION 2.8.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/general.cmake)

set_option(WITH_OPENCV          "Build library with OpenCV"               OFF )
set_option(WITH_FFMPEG          "Build library with FFmpeg"               OFF )

set_option(BUILD_EXAMPLES       "Build Examples"                          ON  )


clear_dependency()
if(WITH_OPENCV)
    add_dependency("opencv")
endif()

if(WITH_FFMPEG)
    add_dependency("ffmpeg")
endif()


add_include("include")
add_lib("mlib" "src" "include")
create_cmake_module("mlib")

if(BUILD_EXAMPLES)
    add_dependency("mlib")
    add_apps("examples")
endif()

set_solution("mlib")
