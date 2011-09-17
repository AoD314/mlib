
cmake_minimum_required(VERSION 2.8)

set(target "mlib" )

project( ${target} )

include_directories("include")

if(UNIX)
	set(WARNING "-Wall -Werror -Wextra -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast ")
	set(WARNING "${WARNING} -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy ")
	set(CMAKE_CXX_FLAGS "-msse4.1 -msse4.2 ${WARNING}")
	
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wnon-virtual-dtor -foptimize-sibling-calls")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -finline-functions -ftree-loop-optimize -floop-parallelize-all")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -fomit-frame-pointer ")
	
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
endif()

file(GLOB src_lib "src/*.cpp")
file(GLOB inc_lib "include/mlib/*.hpp")

add_library( ${target} ${src_lib} ${inc_lib})

# ----------------------------------------------------------------------------
# CHECK_MODULE
# ----------------------------------------------------------------------------

macro(CHECK_MODULE module_name define)
    set(${define} 0)
    if(PKG_CONFIG_FOUND)
        set(ALIAS               ALIASOF_${module_name})
        set(ALIAS_FOUND                 ${ALIAS}_FOUND)
        set(ALIAS_INCLUDE_DIRS   ${ALIAS}_INCLUDE_DIRS)
        set(ALIAS_LIBRARY_DIRS   ${ALIAS}_LIBRARY_DIRS)
        set(ALIAS_LIBRARIES         ${ALIAS}_LIBRARIES)

        PKG_CHECK_MODULES(${ALIAS} ${module_name})

        if (${ALIAS_FOUND})
            set(${define} 1)
            foreach(P "${ALIAS_INCLUDE_DIRS}")
                if (${P})
                    list(APPEND HIGHGUI_INCLUDE_DIRS ${${P}})
                endif()
            endforeach()

            foreach(P "${ALIAS_LIBRARY_DIRS}")
                if (${P})
                    list(APPEND HIGHGUI_LIBRARY_DIRS ${${P}})
                endif()
            endforeach()

            list(APPEND HIGHGUI_LIBRARIES ${${ALIAS_LIBRARIES}})
        endif()
    endif()
endmacro()

# ----------------------------------------------------------------------------


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
# FFMPEG
# ----------------------------------------------------------------------------

set(WITH_FFMPEG OFF CACHE BOOL "Build with FFMPEG")

if(WITH_FFMPEG)

	set(HAVE_FFMPEG 0)
	if(WITH_FFMPEG)
		CHECK_MODULE(libavcodec HAVE_FFMPEG_CODEC)
		CHECK_MODULE(libavformat HAVE_FFMPEG_FORMAT)
		CHECK_MODULE(libavutil HAVE_FFMPEG_UTIL)
		CHECK_MODULE(libswscale HAVE_FFMPEG_SWSCALE)
		CHECK_INCLUDE_FILE(libavformat/avformat.h HAVE_GENTOO_FFMPEG)
		CHECK_INCLUDE_FILE(ffmpeg/avformat.h HAVE_FFMPEG_FFMPEG)

		if(NOT HAVE_GENTOO_FFMPEG AND NOT HAVE_FFMPEG_FFMPEG)
			if(EXISTS /usr/include/ffmpeg/libavformat/avformat.h OR HAVE_FFMPEG_SWSCALE)
				set(HAVE_GENTOO_FFMPEG 1)				
			endif()
		endif()
		
		if(HAVE_FFMPEG_CODEC AND HAVE_FFMPEG_FORMAT AND HAVE_FFMPEG_UTIL)
			if(HAVE_FFMPEG_SWSCALE OR NOT HAVE_GENTOO_FFMPEG)
				set(HAVE_FFMPEG 1)
			endif()
		endif()
		
		if (HAVE_FFMPEG || HAVE_GENTOO_FFMPEG)
			target_link_libraries( ${target} -lavcodec -lavformat -lswscale)
		endif()
		
	endif()
	
endif()

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
if(UNIX)
	install(TARGETS ${target} DESTINATION "/usr/lib")
	find_path(LIB_INCLUDE_PATH string.h)
	install(FILES ${inc_lib} DESTINATION "${LIB_INCLUDE_PATH}/mlib")
endif()

# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# STATUS
# ----------------------------------------------------------------------------
message("")
message("General configuration for mlib ${mlib_version} =====================================")
message("")
message("    Build with FFMPEG  : " ${WITH_FFMPEG})
if (${WITH_FFMPEG})
	message("    FFMPEG:")
	message("      codec:"        ${HAVE_FFMPEG_CODEC}")
	message("      format:        ${HAVE_FFMPEG_FORMAT}")
	message("      util:"         ${HAVE_FFMPEG_UTIL}")
	message("      swscale:"      ${HAVE_FFMPEG_SWSCALE}")
	message("      gentoo-style:" ${HAVE_GENTOO_FFMPEG}")
	message("")
endif()
message("    Build all examples : " ${BUILD_EXAMPLES})
message("    Configuration type : " ${CMAKE_BUILD_TYPE})
message("")
message("    C++ flags (Release): " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
message("    C++ flags (Debug)  : " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
message("")

# ----------------------------------------------------------------------------
