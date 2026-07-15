# > cmake .. -G "Visual Studio 17 2022" -A x64
# OR
# > cmake ..

# > cmake --build . 
# OR
# > cmake --build . --config Release
# OR
# > cmake --build . --config Release

cmake_minimum_required(VERSION 3.30.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FACTORY_METHOD "factory_metod")

project(${FACTORY_METHOD}
  VERSION 0.1.0
  DESCRIPTION "design patterns factory_metod"
  HOMEPAGE_URL "www.merdasecca.org"
  LANGUAGES CXX
)

message("-- CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message("-- CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("-- CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")


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

set(SRC_FILES src/factory_method.cpp)

add_executable(${FACTORY_METHOD} ${SRC_FILES})
