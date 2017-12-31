cmake_minimum_required(VERSION 3.9)
project(graphbasics)

set(CMAKE_CXX_STANDARD 11)

add_executable(graphbasics main.cpp DenseGraph.h SparseGraph.h)