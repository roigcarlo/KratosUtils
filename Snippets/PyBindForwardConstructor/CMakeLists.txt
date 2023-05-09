cmake_minimum_required(VERSION 3.25)

project(Export CXX)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)

pybind11_add_module(ExportAccessor export.cpp)