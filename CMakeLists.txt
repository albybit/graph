cmake_minimum_required(VERSION 3.17)
project(graph)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread )
add_executable(graph main.cpp Graph.cpp Graph.h Path.cpp Path.h)