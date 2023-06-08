cmake_minimum_required(VERSION 3.25)

project(NonEagerCF CXX)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)

set(TF_INCLUDE_DIR /home/roigcarlo/.local/lib/python3.10/site-packages/tensorflow/include)
set(TF_LIBRARY_DIR /home/roigcarlo/.local/lib/python3.10/site-packages/tensorflow)
set(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=1 -DEIGEN_MAX_ALIGN_BYTES=64")

include_directories(${TF_INCLUDE_DIR})
link_directories(${TF_LIBRARY_DIR})

pybind11_add_module(NonEager noneager.cpp)
add_library(AddOp SHARED add_op.cpp)
target_link_libraries(AddOp PUBLIC ":libtensorflow_framework.so.2")