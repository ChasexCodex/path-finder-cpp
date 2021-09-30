cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_LIBRARY true)

add_compile_definitions(INCLUDE_POINT_ON_CIRCLE_EDGE)

if(BUILD_LIBRARY)
    project(path_finder_cpp_shared)

    add_library(path_finder_cpp_shared SHARED library.cpp
            src/arc.cpp
            src/circle_node.cpp
            src/line.cpp
            src/node.cpp
            src/segment.cpp
            src/solver.cpp
            src/helpers.cpp
            library.h)
else()
    project(path_finder_cpp)
    add_executable(path_finder_cpp main.cpp
            src/arc.cpp
            src/circle_node.cpp
            src/line.cpp
            src/node.cpp
            src/segment.cpp
            src/solver.cpp
            src/helpers.cpp
            )

    find_package(RapidJSON CONFIG REQUIRED)
    target_link_libraries(path_finder_cpp PRIVATE rapidjson)
endif()

configure_file(data.json data.json COPYONLY)