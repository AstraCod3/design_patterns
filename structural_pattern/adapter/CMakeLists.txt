
cmake_minimum_required(VERSION 3.30.4)

set(ADAPTER adapter)

project(${ADAPTER}
  VERSION 0.1.0
  DESCRIPTION "design patterns adapter"
  HOMEPAGE_URL "www.merdasecca.org"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    message(STATUS "${PROJ_CLIENT_LIB} Platform Win32")
    if(MSVC)
        message(STATUS "${PROJ_CLIENT_LIB} Compiler MSVC")
    else()
        message(STATUS "${PROJ_CLIENT_LIB} Compiler MinGW")
    endif()
endif()
 
if(LINUX OR UNIX)
    message(STATUS "${PROJ_CLIENT_LIB} Platform Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

set(SRC_FILES src/adapter.cpp)

add_executable(${ADAPTER} ${SRC_FILES})

