
#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/PATConfig.cmake.in" "${CMAKE_BINARY_DIR}/PATConfig.cmake" IMMEDIATE @ONLY)

#set(PAT_CONFIG_FILE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/" CACHE PATH "Where to create the platform-dependant patconfig.hpp")

#message(STATUS "Parsing 'patconfig.h.cmake'")
#configure_file("${CMAKE_CURRENT_SOURCE_DIR}/patconfig.h.cmake" "${PAT_CONFIG_FILE_INCLUDE_DIR}/patconfig.hpp")

# ---------------------------------------------------------------------------
# The C+//0 include & link directories:
# ---------------------------------------------------------------------------

#include_directories("." "${PAT_CONFIG_FILE_INCLUDE_DIR}" "${PAT_CONFIG_FILE_INCLUDE_DIR}")

# -------------------------------------------------------------------------------------------
#  Part 1/3: ${BIN_DIR}/PATConfig.cmake              -> For use *without* "make install"
# -------------------------------------------------------------------------------------------
#set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "\"${PAT_CONFIG_FILE_INCLUDE_DIR}\" \"${CMAKE_CURRENT_SOURCE_DIR}/include\" \"${CMAKE_CURRENT_SOURCE_DIR}/lib/include\" ")
#set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Output directory for libraries" )
#set(CMAKE_LIB_DIRS_CONFIGCMAKE "${LIBRARY_OUTPUT_PATH}")

#      - OpenCV_LIBS                     : The list of libraries to links against.
#      - OpenCV_LIB_DIR                  : The directory(es) where lib files are. Calling LINK_DIRECTORIES
#                                          with this path is NOT needed.
#      - OpenCV_INCLUDE_DIRS             : The OpenCV include directories.
#      - OpenCV_COMPUTE_CAPABILITIES     : The version of compute capability
#      - OpenCV_ANDROID_NATIVE_API_LEVEL : Minimum required level of Android API
#      - OpenCV_VERSION                  : The version of this OpenCV build: "2.4.9"
#      - OpenCV_VERSION_MAJOR            : Major version part of OpenCV_VERSION: "2"
#      - OpenCV_VERSION_MINOR            : Minor version part of OpenCV_VERSION: "4"
#      - OpenCV_VERSION_PATCH            : Patch version part of OpenCV_VERSION: "9"
#      - OpenCV_VERSION_TWEAK  

macro(create_cmake_module config_name)
	# write _LIBS _LIB_DIR _INCLUDE_DIRS 
	string(TOUPPER       "${config_name}" PROJECT)
	set(PROJECT_LIBS     "${LAST_PROJECT_LIBRARY}")
	set(PROJECT_LIB_DIR  "\"${CMAKE_BINARY_DIR}/lib/\"")
	status("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
	status("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
	configure_file("${CMAKE_SOURCE_DIR}/cmake/template.cmake.in" "${CMAKE_BINARY_DIR}/${config_name}.cmake" IMMEDIATE @ONLY)
endmacro()

macro(create_config file_name)
	status("Parsing ${file_name}")
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${file_name}.cmake" "${file_name}")
endmacro()
