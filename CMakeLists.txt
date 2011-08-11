
cmake_minimum_required(VERSION 2.8)

set(target "mlib" )

project( ${target} )

include_directories("include")

set(WARNING "-Wall -Werror -Wextra -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast ")
set(WARNING "${WARNING} -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy ")
set(CMAKE_CXX_FLAGS "-msse4.1 -msse4.2 ${WARNING}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wnon-virtual-dtor -foptimize-sibling-calls")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -finline-functions -ftree-loop-optimize") 

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -fomit-frame-pointer ")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 ")

file(GLOB src_lib "src/*.cpp")
file(GLOB inc_lib "include/mlib/*.hpp")

add_library( ${target} SHARED ${src_lib} ${inc_lib})
target_link_libraries( ${target} -lavcodec -lavformat )

# ----------------------------------------------------------------------------
# CONFIGURE
# ----------------------------------------------------------------------------

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

#set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
#if(DEFINED CMAKE_BUILD_TYPE)
#	set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
#endif()

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

set(BUILD_EXAMPLES ON CACHE BOOL "Build all examples")

if(BUILD_EXAMPLES)

	file(GLOB examples_list "examples/*.cpp")

	FOREACH(ex ${examples_list})
		string(REGEX REPLACE "^.*/(.+).cpp" "\\1" ex_name ${ex})
		add_executable( ${ex_name} ${ex} )
		target_link_libraries( ${ex_name} "mlib" )
	ENDFOREACH()

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
message("    Build all examples : " ${BUILD_EXAMPLES})
message("    Configuration type : " ${CMAKE_BUILD_TYPE})
message("")
message("    C++ flags (Release): " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
message("    C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
message("")

# ----------------------------------------------------------------------------
