cmake_minimum_required(VERSION 3.25)

project(TensorView CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(include)

add_executable(TensorView "src/main.cpp")

install(TARGETS TensorView DESTINATION "bin/")