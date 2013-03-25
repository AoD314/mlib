
# need clang >=3.2

if(CXX_CLANG)

	if(${ENABLE_C++11})
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
	    set(CMAKE_C_FLAGS     "${CMAKE_C_FLAGS} -std=c++11 ")
	endif()

endif()