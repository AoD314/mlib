
macro(add_app project_name)
    project(${project_name})

    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/")

    unset(folders)
    set(folders)
    unset(files)
    set(files)


    foreach(arg ${ARGN})
        if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${arg}/")
            list(APPEND folders ${arg})
            status("folders += ${arg}")
        else()
            list(APPEND files ${arg})
            status("files   += ${arg}")
        endif()
    endforeach()
  
    status(" ")
    status("---------------------------------------------------")
    status("add_application:")
    status("        name        : [${project_name}]")
    status("        files       : [${files}]")
    status("        folders     : [${folders}]")

    list(LENGTH folders folders_len)
    if(NOT ${folders_len} EQUAL 0)
        get_all_files_for_build(${folders})
    else()
        unset(target_global_list_code)
        unset(target_global_list_moc_code)
    endif()

    add_executable       (${project_name} ${target_global_list_code} ${files} ${target_global_list_moc_obj})
    target_link_libraries(${project_name} ${target_global_list_libs})
    
    print_status()
    status("---------------------------------------------------")
    status(" ")
endmacro()

macro(add_apps folder_name)

    file(GLOB applications_list "${folder_name}/*.cpp")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/")

    status("add_applications:")

    foreach(ex ${applications_list})
        string(REGEX REPLACE "^.*/(.+).cpp" "\\1" ex_name ${ex})
        status("        name        : [${ex_name}]")
        status("        sources     : [${ex}]")
        
        project(${ex_name} CXX)
        add_executable       (${ex_name} ${ex})
        target_link_libraries(${ex_name} ${target_global_list_libs})
    endforeach()

    print_status()
endmacro()
