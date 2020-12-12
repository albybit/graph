cmake_minimum_required(VERSION 3.17)
project(linkedlist)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(Boost_INCLUDE_DIR /usr/include)
set(Boost_LIBRARY_DIR /usr/lib64)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR}
        set(CMAKE_CXX_STANDARD 14)
        SET(CMAKE_CXX_FLAGS -pthread ))
add_executable(linkedlist main.cpp Graph.cpp Graph.h)