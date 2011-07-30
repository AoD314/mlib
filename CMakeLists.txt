
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


# ----------------------------------------------------------------------------
# CONFIGURE
# ----------------------------------------------------------------------------

set(BUILD_EXAMPLES ON CACHE BOOL "Build all examples")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
	set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
endif()

# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
#  Get actual mlib version number from sources
# ----------------------------------------------------------------------------
set(mlib_version_file "${CMAKE_CURRENT_SOURCE_DIR}/include/mlib/version.hpp")
file(STRINGS "${mlib_version_file}" mlib_version_parts REGEX "#define MLIB_.+OR_VERSION[ ]+[0-9]+" )
string(REGEX REPLACE ".+MLIB_MAJOR_VERSION[ ]+([0-9]+).*" "\\1" MLIB_MAJOR_VERSION "${mlib_version_parts}")
string(REGEX REPLACE ".+MLIB_MINOR_VERSION[ ]+([0-9]+).*" "\\1" MLIB_MINOR_VERSION "${mlib_version_parts}")
string(REGEX REPLACE ".+MLIB_SUBMINOR_VERSION[ ]+([0-9]+).*" "\\1" MLIB_SUBMINOR_VERSION "${mlib_version_parts}")
set(mlib_version "${MLIB_MAJOR_VERSION}.${MLIB_MINOR_VERSION}.${MLIB_SUBMINOR_VERSION}")
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# EXAMPLES
# ----------------------------------------------------------------------------

if(BUILD_EXAMPLES)

	set(ex1 "example_timer")
	add_executable( ${ex1} "examples/example_timer.cpp" )
	target_link_libraries( ${ex1} "mlib" )

	set(ex2 "example_convert")
	add_executable( ${ex2} "examples/example_convert.cpp" )
	target_link_libraries( ${ex2} "mlib" )

	set(ex3 "example_console_parameters")
	add_executable( ${ex3} "examples/example_console_parameters.cpp" )
	target_link_libraries( ${ex3} "mlib" )

	set(ex4 "example_progress_bar")
	add_executable( ${ex4} "examples/example_progress_bar.cpp" )
	target_link_libraries( ${ex4} "mlib" )
endif()
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# INSTALL
# ----------------------------------------------------------------------------

install(TARGETS ${target} DESTINATION "/usr/lib")
find_path(LIB_INCLUDE_PATH string.h)
install(FILES ${inc_lib} DESTINATION "${LIB_INCLUDE_PATH}/mlib")
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# STATUS
# ----------------------------------------------------------------------------
message("")
message("General configuration for mlib ${mlib_version} =====================================")
message("")
message("    Build all examples: " ${BUILD_EXAMPLES})
message("")

# ----------------------------------------------------------------------------
