
macro(add_application project_name)
    project(${project_name})

    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/")

    unset(folders)
    set(folders)

    foreach(arg ${ARGN})
        list(APPEND folders ${arg})
    endforeach()
  
    status("add_application:")
    status("        name        : [${project_name}]")
    status("        folders     : [${folders}]")
    get_all_files_for_build(${folders})

    add_executable       (${project_name} ${target_global_list_code} ${target_global_list_moc_obj})
    target_link_libraries(${project_name} ${target_global_list_libs})
    
    print_status()

endmacro()
