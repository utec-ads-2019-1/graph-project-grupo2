cmake_minimum_required(VERSION 3.10)
project(graph-project-grupo2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(graph
        edge.h
        graph.h
        graph.hpp
        main.cpp
        node.h
        read.hpp
        disjoin
        interface.h

        )
