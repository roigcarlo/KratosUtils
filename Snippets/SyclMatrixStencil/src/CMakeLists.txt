cmake_minimum_required(VERSION 3.24)
project(SyclMatrixStencil CXX)

set(CMAKE_CXX_STANDARD 17)

set(SYCL_FLAGS "-fsycl -fsycl-targets=nvptx64-nvidia-cuda -fsycl-unnamed-lambda")
find_package(IntelSYCL REQUIRED)

include_directories(${SYCL_INCLUDE_DIR})

add_executable(SyclMatrixStencil main.cpp)
add_sycl_to_target(TARGET SyclMatrixStencil SOURCES main.cpp)

install(TARGETS SyclMatrixStencil)