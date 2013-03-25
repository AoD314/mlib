
macro(set_dependency)

  unset(target_global_list_libs)
  set(target_global_list_libs)
  
  set(target_use_qt FALSE)
  
  foreach(arg ${ARGV})
    if (arg STREQUAL "opencv")
      find_package(OpenCV REQUIRED)
      list(APPEND target_global_list_libs ${OpenCV_LIBS})


    elseif(arg STREQUAL "ffmpeg")
      find_package(FFMPEG REQUIRED)
      list(APPEND target_global_list_libs ${FFMPEG_LIBRARIES})


    elseif(arg STREQUAL "gtest")
      find_package(GTest REQUIRED)
      list(APPEND target_global_list_libs ${GTEST_LIBRARIES})


    elseif(arg STREQUAL "pat")
      find_package(PAT REQUIRED)
      list(APPEND target_global_list_libs ${PAT_LIBRARIES})


    elseif(arg STREQUAL "webp")
      find_package(WebP REQUIRED)
      list(APPEND target_global_list_libs ${WEBP_LIBRARIES})


    elseif(arg STREQUAL "sdl")
      find_package(SDL REQUIRED)
      list(APPEND target_global_list_libs ${SDL_LIBRARY})


    elseif(arg STREQUAL "qt4")
      set(target_use_qt TRUE)
      find_package(Qt4 4.8.0 COMPONENTS QtCore QtGui QtOpenGL QtScript QtNetwork REQUIRED)
      include(${QT_USE_FILE})
      include_directories( ${QT_INCLUDE_DIR} )
      list(APPEND target_global_list_libs ${QT_LIBRARIES})


    elseif(arg STREQUAL "tbb")
      find_package(TBB REQUIRED)
      list(APPEND target_global_list_libs ${TBB_LIBRARIES})


    elseif(arg STREQUAL "opengl")
      find_package(OpenGL REQUIRED)
      list(APPEND target_global_list_libs ${OPENGL_LIBRARIES})
      find_package(GLEW REQUIRED)
      list(APPEND target_global_list_libs ${GLEW_LIBRARIES})


    elseif()
      status("Unknown option: ${arg}")
    endif()
  endforeach()
endmacro()

