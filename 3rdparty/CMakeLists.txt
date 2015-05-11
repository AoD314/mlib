set(project_name "gtest")
project(${project_name})

if((CXX_GCC OR CXX_CLANG) AND (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(Pthread "-pthread")
endif()

if(CXX_MS)
    set(CMAKE_CXX_FLAGS "/EHsc")
else()
    set(CMAKE_CXX_FLAGS "")
endif()

add_lib_static(${project_name} "gtest/gtest-all.cc" "gtest/gtest.h")
target_link_libraries(${project_name} ${Pthread})
