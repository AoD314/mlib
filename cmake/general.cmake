
########################################
# 
# list of global variables:
# 
# * target_name (str)
# * target_global_list_libs (list)
# * target_use_qt (bool)
# * target_global_list_code (list)
# * target_global_list_moc_code (list)
# * target_global_list_moc_obj (list)
# 
########################################

########################################
#
# list of global function 
# * add_include
# * add_app
# * add_apps
# * add_lib
# * set_solution
# * set_option
# * clear_dependency()
# * add_dependency("name")
# * create_cmake_module("module_name")
# * 
# * 
########################################


########################################
#
# cmake_minimum_required(VERSION 2.8.6)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# include(cmake/general.cmake)
# 
########################################

macro(set_solution name)
  set(target_name ${name})
  project(${target_name})
endmacro()

include(project_utils REQUIRED)
include(dependency REQUIRED)

include(config REQUIRED)

include(status REQUIRED)
include(compiler REQUIRED)

macro(print_status)
    status("    sources: ")
    foreach(s ${target_global_list_code})
        status("        ${s}")
    endforeach()

    status("    libraries: ")
    foreach(l ${target_global_list_libs})
    	if((${l} STREQUAL "debug") OR (${l} STREQUAL "optimized"))
    		
    	else()
    		status("        ${l}")
    	endif()
    endforeach()

    if (target_use_qt)
        status("    moc objects: ")
        foreach(m ${target_global_list_moc_obj})
            status("        ${m}")
        endforeach()
    endif()
endmacro()

include(add_library REQUIRED)
include(add_application REQUIRED)
