
# ----------------------------------------------------------------------------
# post build event
# ----------------------------------------------------------------------------
#add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)
#add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/trans)
#add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/trans)

#foreach(LANGUAGE ${LANGUAGES})
#    set(TS ${TRANSLATIONS_PATH}/${LANGUAGESAGE}.ts)
#    add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND
#        ${CMAKE_COMMAND} -E copy
#        ${CMAKE_CURRENT_SOURCE_DIR}/resources/translations/${LANGUAGE}.qm ${CMAKE_BINARY_DIR}/trans)
#    add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND
#        ${CMAKE_COMMAND} -E copy
#        ${CMAKE_CURRENT_SOURCE_DIR}/resoADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_DEFINITIONS(-DQT_PLUGIN)
#ADD_DEFINITIONS(-DQT_SHARED)urces/translations/${LANGUAGE}.qm
#        ${CMAKE_BINARY_DIR}/bin/trans)
#endforeach()

#if(WIN32)
#    if(MSVC)
#        add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/$(ConfigurationName)/pat.dll ${CMAKE_BINARY_DIR}/bin)
#        add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/$(ConfigurationName)/pat.lib ${CMAKE_BINARY_DIR}/bin)
#        add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/$(ConfigurationName)/pat_gui.exe ${CMAKE_BINARY_DIR}/bin)
#    else()
#        add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/libpat.dll ${CMAKE_BINARY_DIR}/bin)
#        add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/libpat.dll.a ${CMAKE_BINARY_DIR}/bin)
#        add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/pat_gui.exe ${CMAKE_BINARY_DIR}/bin)
#    endif()
#else()
#    add_custom_command( TARGET ${target_lib} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_OUTPUT_PATH}/libpat.* ${CMAKE_BINARY_DIR}/bin)
#    add_custom_command( TARGET ${target_gui} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/pat_gui ${CMAKE_BINARY_DIR}/bin)
#endif()
# ----------------------------------------------------------------------------

