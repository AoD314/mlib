cmake_minimum_required(VERSION 2.8.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/general.cmake)

set_option(WITH_FFMPEG          "Build library with FFmpeg"               OFF )
set_option(WITH_WEBP            "Build library with WebP"                 ON  )
set_option(WITH_VPX             "Build library with libvpx"               ON  )

set_option(BUILD_EXAMPLES       "Build Examples"                          ON  )
set_option(BUILD_TESTS          "Build Tests"                             ON  )


clear_dependency()

if(WITH_FFMPEG)
    add_dependency("ffmpeg")
endif()

if(WITH_WEBP)
    add_dependency("webp")
endif()

if(WITH_VPX)
    add_dependency("vpx")
endif()

add_include("include")
add_lib("mlib" "src" "include")
create_cmake_module("mlib")

if(BUILD_EXAMPLES)
    add_dependency("mlib")
    add_apps("examples")
endif()

if(BUILD_TESTS)
    add_dependency("mlib" "gtest")
    add_app("test_mlib" "tests")
endif()

set_solution("mlib")
