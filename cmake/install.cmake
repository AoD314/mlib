
# ----------------------------------------------------------------------------
# INSTALL
# ----------------------------------------------------------------------------

if(UNIX)
    install(TARGETS ${target} DESTINATION "/usr/lib")
    find_path(LIB_INCLUDE_PATH string.h)
    install(FILES ${inc_lib} DESTINATION "${LIB_INCLUDE_PATH}/pat")
endif()

# ----------------------------------------------------------------------------
