cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_LIBRARY true)

# SETTINGS TO MODIFY THE REQUIREMENTS OF THE PATH FINDER
add_compile_definitions(INCLUDE_POINT_ON_CIRCLE_EDGE)
add_compile_definitions(USE_MACROS)
add_compile_definitions(USE_LIMIT)

if(BUILD_LIBRARY)
    set(CPP_PROJECT_NAME path_finder_cpp_shared)
else()
    set(CPP_PROJECT_NAME path_finder_cpp)
endif()

if(true)
    add_compile_definitions(ASTAR)
else()
    add_compile_definitions(DIJKSTRA)
endif()

project("${CPP_PROJECT_NAME}")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    add_compile_definitions(DEFAULT_MSVC)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    add_compile_definitions(WSL_GCC)
endif ()

if (BUILD_LIBRARY)
    add_library(path_finder_cpp_shared SHARED library.cpp
            src/arc.cpp
            src/circle_node.cpp
            src/line.cpp
            src/node.cpp
            src/segment.cpp
            src/solver.cpp
            src/helpers.cpp)
else ()
    # unbundled
#    add_executable(path_finder_cpp main.cpp
#            src/arc.cpp
#            src/circle_node.cpp
#            src/line.cpp
#            src/node.cpp
#            src/segment.cpp
#            src/solver.cpp
#            src/helpers.cpp)
    add_executable(path_finder_cpp main.cpp
            function.cpp)

    find_package(RapidJSON CONFIG REQUIRED)
    target_link_libraries("${CPP_PROJECT_NAME}" PRIVATE rapidjson)
endif ()

configure_file(data.json data.json COPYONLY)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries("${CPP_PROJECT_NAME}" PRIVATE
        GTest::gmock
        GTest::gtest
        GTest::gmock_main
        GTest::gtest_main)

add_test(GTest::gtest_main gtest_main)