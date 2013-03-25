
cmake_minimum_required(VERSION 2.8.6)

################# define compilers #################

if(NOT APPLE)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_GNUCXX 1)
  endif()
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_GNUCC 1)
  endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CXX_CLANG 1)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CXX_GCC 1)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	set(CXX_INTEL 1)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CXX_MS 1)
endif()

###################################################

set_option(ENABLE_C++11                 "Support C++11"                                               ON   )
set_option(ENABLE_PROFILING             "Enable profiling in the GCC compiler (Add flags: -g -pg)"    OFF  IF (CXX_GCC) )
set_option(ENABLE_FAST_MATH             "Enable -ffast-math"                                          OFF  IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG) )
set_option(ENABLE_SSE                   "Enable SSE instructions"                                     ON   IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG OR CXX_MS) )
set_option(ENABLE_SSE2                  "Enable SSE2 instructions"                                    ON   IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG OR CXX_MS) )
set_option(ENABLE_SSE3                  "Enable SSE3 instructions"                                    ON   IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG) )
set_option(ENABLE_SSSE3                 "Enable SSSE3 instructions"                                   ON   IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG) )
set_option(ENABLE_SSE41                 "Enable SSE4.1 instructions"                                  ON   IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG) )
set_option(ENABLE_SSE42                 "Enable SSE4.2 instructions"                                  ON   IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG) )
set_option(ENABLE_AVX                   "Enable AVX instructions"                                     OFF  IF (CXX_INTEL OR CXX_GCC OR CXX_CLANG) )

set_option(ENABLE_ALLWARNING            "Show all warnings even if they are too noisy"                OFF  )
set_option(ENABLE_WARNINGS_ARE_ERRORS   "Treat warnings as errors"                                    OFF  )

set_option(ENABLE_OPENMP                "Enamble OpenMP"                                              OFF  IF (CXX_MS OR CXX_GCC OR CXX_INTEL) )
set_option(ENABLE_DEBUG_INFO            "Add debug info"                                              ON   )
set_option(ENABLE_RELEASE               "Build RELEASE"                                               OFF  )
set_option(CMAKE_VERBOSE                "Verbose mode"                                                OFF  )

############## include all compilers #############

include(compiler_gcc)
include(compiler_clang)
include(compiler_ms)

status("compiler flags: ${CMAKE_CXX_FLAGS}")

###################################################
