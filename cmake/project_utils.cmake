
macro(set_option variable description value)
  set(__value ${value})
  set(__condition "")
  set(__varname "__value")
  foreach(arg ${ARGN})
    if(arg STREQUAL "IF" OR arg STREQUAL "if")
      set(__varname "__condition")
    else()
      list(APPEND ${__varname} ${arg})
    endif()
  endforeach()

  unset(__varname)
  if("${__condition}" STREQUAL "")
    set(__condition 2 GREATER 1)
  endif()

  if(${__condition})
    if("${__value}" MATCHES ";")
      if(${__value})
        option(${variable} "${description}" ON)
      else()
        option(${variable} "${description}" OFF)
      endif()
    elseif(DEFINED ${__value})
      if(${__value})
        option(${variable} "${description}" ON)
      else()
        option(${variable} "${description}" OFF)
      endif()
    else()
      option(${variable} "${description}" ${__value})
    endif()
  else()
    unset(${variable} CACHE)
  endif()
  unset(__condition)
  unset(__value)
endmacro()


macro(add_include)
  unset(PROJECT_INCLUDE_DIRS)
  set(PROJECT_INCLUDE_DIRS)
  foreach(arg ${ARGV})
    status("add to include  : ${CMAKE_CURRENT_SOURCE_DIR}/${arg}")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${arg}")
    list(APPEND PROJECT_INCLUDE_DIRS "\"${CMAKE_CURRENT_SOURCE_DIR}/${arg}\"")
  endforeach()
endmacro()

macro(check_moc_file file)
  file(STRINGS "${file}" lists_OBJS REGEX ".*Q_OBJECT.*")
  string(STRIP "${lists_OBJS}" str_str)
  string(COMPARE EQUAL "Q_OBJECT" "${str_str}" MOC_FILE_OBJ)

  file(STRINGS "${file}" lists_OBJS REGEX "include.*Qt.*")
  string(STRIP "${lists_OBJS}" str_str)
  string(COMPARE NOTEQUAL "" "${str_str}" MOC_FILE_INC)

  if(${MOC_FILE_OBJ} OR ${MOC_FILE_INC})
    set(IS_MOC_FILE TRUE)
  else()
    set(IS_MOC_FILE FALSE)
  endif()
endmacro()


macro(get_all_files_for_build)
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  unset(target_global_list_code)
  unset(target_global_list_moc_code)

  set(target_global_list_code)
  set(target_global_list_moc_code)

  foreach(arg ${ARGV})
    file(GLOB_RECURSE srcs "${arg}/*.cpp")
    file(GLOB_RECURSE hdrs "${arg}/*.hpp")

    status("add to include  : " ${arg})
    include_directories("${arg}")

    foreach(src ${srcs})
        list(APPEND target_global_list_code ${src})
    endforeach()

    foreach(hdr ${hdrs})
      if (target_use_qt)
        check_moc_file(${hdr})
        if (IS_MOC_FILE)
          list(APPEND target_global_list_moc_code ${hdr})  
        else()
          list(APPEND target_global_list_code ${hdr})
        endif()
      else()
        list(APPEND target_global_list_code ${hdr})
      endif()
    endforeach()
  endforeach()

  list(LENGTH target_global_list_code len_list)
  unset(target_global_list_moc_obj)

  if (${len_list} LESS 1)
    message(FATAL_ERROR "Source files not found in ${ARGV}!!!")
  endif()

  if (target_use_qt)
    list(LENGTH target_global_list_moc_code length_moc_list)
    if (${length_moc_list} GREATER 0)
      qt4_wrap_cpp(target_global_list_moc_obj ${target_global_list_moc_code})
    endif()
  endif()
endmacro()