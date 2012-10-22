cmake_minimum_required(VERSION 2.8.9)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectUtils.cmake)

create_project("test_project")

set_dependency(opencv)

add_application("src")