cmake_minimum_required(VERSION 2.8)
project(pentarabbit)

include(FindOpenMP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_executable(${PROJECT_NAME} main.cpp Algebre.cpp Cycle.cpp Julia.cpp lodepng.cpp Dynamicien.cpp)

find_package (Threads)
find_package(SFML 2 REQUIRED graphics window system)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
