
cmake_minimum_required(VERSION 2.8)

set(target "mlib" )

project( ${target} )

include_directories("include")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -msse4.1 -msse4.2 -fopenmp ")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Werror -Wextra ")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -pipe -fomit-frame-pointer ")

file(GLOB src_lib "src/*.cpp")
file(GLOB inc_lib "include/mlib/*.hpp")

add_library( ${target} ${src_lib} ${inc_lib})
target_link_libraries( ${target} "gomp" )


set(ex1 "example01")
add_executable( ${ex1} "examples/example01.cpp" )
target_link_libraries( ${ex1} "mlib" )

set(ex2 "example02")
add_executable( ${ex2} "examples/example02.cpp" )
target_link_libraries( ${ex2} "mlib" )

set(ex3 "example03")
add_executable( ${ex3} "examples/example03.cpp" )
target_link_libraries( ${ex3} "mlib" )
