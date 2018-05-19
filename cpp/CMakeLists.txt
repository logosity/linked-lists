cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)

project(dx coding problem)

file(GLOB SOURCES "src/*.cpp")
file(GLOB SPECS "spec/*.cpp")

include_directories(include)

add_executable(spec ${SPECS} "src/main.cpp")
