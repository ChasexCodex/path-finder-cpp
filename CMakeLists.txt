cmake_minimum_required(VERSION 3.20)
project(path_finder_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(path_finder_cpp main.cpp src/point.h src/circle.h src/line.h src/segment.h src/arc.h src/solver.h src/node.h src/circle_node.h src/helpers.h)
