# path-finder-cpp
Astar pathfinding implementation in C++

This source code was made to solve the kata (challenge) on Codewars at https://www.codewars.com/kata/58b617f15705ae68cc0000a9
, recording me as the 22th person world wide to solve it.

Features and key characteristics:
 - 
 - Performance (maximum of 1 second for a sample of 300 obstalces).
 - Can read JSON data (in the form of Unity Engine's serialized data).
 - Exposing utilities so it can be used with other projects (Personally used with my C# implementation and visualization).
 - Implements both AStar and Dijkstra algorithms, with the algorithm chosen at compile time.
 - Supports MSVC and GCC compilers (uses CMake).
 - Has two ways of implementing, macros and inline functions, specified at compile time.
