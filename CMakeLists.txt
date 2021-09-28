cmake_minimum_required(VERSION 3.20)
project(path_finder_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(path_finder_cpp main.cpp
        src/arc.cpp
        src/circle_node.cpp
        src/line.cpp
        src/node.cpp
        src/segment.cpp
        src/solver.cpp
        src/helpers.cpp)

#add_executable(path_finder_cpp main.cpp function.cpp)