cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)

project(DeepCopyOptimization)

file(GLOB SOURCES "src/*.cpp")
file(GLOB SPECS "spec/*.cpp")

include_directories(include)

add_executable(graphs ${SOURCES})
add_executable(spec ${SPECS} src/list.cpp)
