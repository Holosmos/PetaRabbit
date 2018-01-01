cmake_minimum_required(VERSION 2.8)
project(pentarabbit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_executable(${PROJECT_NAME} main.cpp Algebre.cpp Cycle.cpp Julia.cpp lodepng.cpp)

find_package (Threads)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
