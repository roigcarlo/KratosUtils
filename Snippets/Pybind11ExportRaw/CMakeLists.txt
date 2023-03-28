cmake_minimum_required(VERSION 3.25)

project(Binding CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)

pybind11_add_module(BindModule bind.cpp)