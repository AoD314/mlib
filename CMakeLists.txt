cmake_minimum_required(VERSION 3.2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/general.cmake)

set_option(BUILD_EXAMPLES       "Build Examples"                          ON  )
set_option(BUILD_TESTS          "Build Tests"                             ON  )
set_option(BUILD_DOCUMENTATION  "Build Documentation"                     OFF )

if(BUILD_DOCUMENTATION)
    add_documentation(docs docs/Doxyfile.in)
endif()

add_dir_inc("include")
add_lib_shared("mlib" "src" "include/mlib")
create_cmake_module("mlib")

if(BUILD_EXAMPLES)
    add_local_dependency("mlib")
    add_apps("examples")
endif()

if(BUILD_TESTS)
    include_directories(SYSTEM "3rdparty")
    add_subdirectory("3rdparty")
    add_local_dependency("mlib" "gtest")
    add_app("unittest_mlib" "tests")
endif()

set_solution("mlib")
