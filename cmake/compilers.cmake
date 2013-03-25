
set(ENABLE_ALLWARNING  TRUE   CACHE BOOL "Compile with all warning"     )
set(ENABLE_DEBUG_INFO  TRUE   CACHE BOOL "Add debug info"               )
set(ENABLE_PROFILING   FALSE  CACHE BOOL "Compile with profiling flags" )

set(ENABLE_SSE2   TRUE   CACHE BOOL "ENABLE SSE2"   )
set(ENABLE_SSE3   FALSE  CACHE BOOL "ENABLE SSE3"   )
set(ENABLE_SSE4   FALSE  CACHE BOOL "ENABLE SSE4"   )
set(ENABLE_AVX    FALSE  CACHE BOOL "ENABLE AVX"    )
set(ENABLE_OPENMP FALSE  CACHE BOOL "ENABLE OpenMP" )
set(ENABLE_C++11  TRUE   CACHE BOOL "Support C++11" )

if(NOT MSVC)
    if(${ENABLE_DEBUG_INFO})
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -O0 -g ")
    else()
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -O3 ")
    endif()

    if(${ENABLE_ALLWARNING})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wenum-compare ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Weffc++ -Wconversion -Wsign-conversion -Wold-style-cast -Wunreachable-code -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wenum-compare ")
    endif()

    if(${ENABLE_PROFILING})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -pg ")
    endif()

    if(${ENABLE_SSE2})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -msse2 ")
    endif()

    if(${ENABLE_SSE3})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -msse3 ")
    endif()

    if(${ENABLE_SSE4})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 ")
        set(CMAKE_C_FLAGS   "  ${CMAKE_C_FLAGS} -msse4.2 ")
    endif()

    if(${ENABLE_AVX})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -mavx ")
    endif()

    if(${ENABLE_OPENMP})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mopenmp ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -mopenmp ")
    endif()

    if(${ENABLE_C++11})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -std=c++0x ")
    endif()

else()

    include(ProcessorCount)
    ProcessorCount(N)
    if(NOT N EQUAL 0)
        SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /MP${N} ")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP${N} ")
    endif()

    if(${ENABLE_SSE2})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /arch:SSE2 ")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}    /arch:SSE2 ")
    endif()

    if(${ENABLE_SSE4})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /arch:SSE4.1 ")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}    /arch:SSE4.1 ")
    endif()

    if(${ENABLE_OPENMP})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /openmp ")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}    /openmp ")
    endif()

endif()
