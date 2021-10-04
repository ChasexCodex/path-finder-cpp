cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_LIBRARY false)

# SETTINGS TO MODIFY THE REQUIREMENTS OF THE PATH FINDER
add_compile_definitions(INCLUDE_POINT_ON_CIRCLE_EDGE)
add_compile_definitions(USE_MACROS)
add_compile_definitions(USE_LIMIT)

if(true)
    add_compile_definitions(ASTAR)
else()
    add_compile_definitions(DIJKSTRA)
endif()

if (BUILD_LIBRARY)
    project(path_finder_cpp_shared)

    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
        add_compile_definitions(DEFAULT_MSVC)
    elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        add_compile_definitions(WSL_GCC)
    endif ()

    add_library(path_finder_cpp_shared SHARED library.cpp
            src/arc.cpp
            src/circle_node.cpp
            src/line.cpp
            src/node.cpp
            src/segment.cpp
            src/solver.cpp
            src/helpers.cpp
            library.h src/definitions.h)
else ()
    project(path_finder_cpp)

    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_definitions(DEFAULT_MSVC)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_definitions(WSL_GCC)
    endif ()

    add_executable(path_finder_cpp main.cpp
            src/arc.cpp
            src/circle_node.cpp
            src/line.cpp
            src/node.cpp
            src/segment.cpp
            src/solver.cpp
            src/helpers.cpp
            function.cpp)

    find_package(RapidJSON CONFIG REQUIRED)
    target_link_libraries(path_finder_cpp PRIVATE rapidjson)
endif ()

configure_file(data.json data.json COPYONLY)