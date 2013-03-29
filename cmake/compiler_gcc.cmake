
# need gcc >=4.7.1

if(CXX_GCC)
    exec_program(${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE _compiler_output)
    string(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9])" "\\1" gcc_compiler_version ${_compiler_output})
    message(STATUS "C++ compiler version: ${gcc_compiler_version} [${CMAKE_CXX_COMPILER}]")

    if(${ENABLE_WARNINGS_ARE_ERRORS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -Werror ")
    endif()

    if(${ENABLE_C++11})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -std=c++11 ")
    endif()

    if(${ENABLE_DEBUG_INFO})
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -g ")
    endif()

    if(${ENABLE_RELEASE})
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -O3 ")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -O0 ")
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

    if(${ENABLE_SSSE3})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3 ")
        set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -mssse3 ")
    endif()

    if(${ENABLE_SSE41})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 ")
        set(CMAKE_C_FLAGS   "  ${CMAKE_C_FLAGS} -msse4.1 ")
    endif()

    if(${ENABLE_SSE42})
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

endif()
