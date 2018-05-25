cmake_minimum_required(VERSION 3.5.1)

project(DeepCopyOptimization C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g -O0")

include_directories(include)

set(C_SOURCES "src/list.c" )
file(GLOB SPECS "spec/*.cpp")
file(GLOB BENCHMARKS "benchmarks/*.cpp")
set(C_SOURCES_MAIN  "benchmarks/bench_helpers.cpp" "src/main.cpp" ${C_SOURCES})

add_executable(main ${C_SOURCES_MAIN})
add_executable(spec ${SPECS} ${C_SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(bench ${BENCHMARKS} ${C_SOURCES} )
target_link_libraries(bench Threads::Threads benchmark)
