
macro(add_lib project_name)
    project(${project_name} CXX)

    set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib/")

    unset(LAST_PROJECT_LIBRARY)
    set(LAST_PROJECT_LIBRARY "${project_name}")

    unset(folders)
    set(folders)

    foreach(arg ${ARGN})
        list(APPEND folders ${arg})
        status("folders += ${arg}")
    endforeach()

    status("add_static_library:")
    status("        name        : [${project_name}]")
    status("        folders     : [${folders}]")
    get_all_files_for_build(${folders})

    add_library          (${project_name} STATIC ${target_global_list_code} ${target_global_list_moc_obj})
    target_link_libraries(${project_name}        ${target_global_list_libs})

    print_status()
    
endmacro()
