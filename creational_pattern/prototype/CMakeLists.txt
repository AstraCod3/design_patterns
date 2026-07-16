# > cmake .. -G "Visual Studio 17 2022" -A x64
# > cmake --build . --config Release

cmake_minimum_required(VERSION 3.30.4)

project(prototype)

add_executable(prototype prototype.cpp)