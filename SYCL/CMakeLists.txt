cmake_minimum_required (VERSION 3.24.0)

project (B0_MEETINGS_SYCL CXX)

find_package(TBB REQUIRED)
find_package(IntelSYCL REQUIRED)

include_directories("src")
include_directories(${SYCL_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-qopenmp")
set(SYCL_CPU_FLAGS -fsycl -fsycl-targets=spir64_x86_64 -fsycl-unnamed-lambda)
set(SYCL_GPU_FLAGS -fsycl -fsycl-targets=nvptx64-nvidia-cuda -fsycl-unnamed-lambda -fp-model=precise)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(VEC_SCAL "src/example_1/vec_scal.cpp")
add_executable(VEC_SYCL_CPU "src/example_2/vec_sycl.cpp")
add_executable(VEC_SYCL_GPU "src/example_2/vec_sycl.cpp")
add_executable(VEC_MEMO_CPU "src/example_3/vec_memo.cpp")
add_executable(VEC_MEMO_GPU "src/example_3/vec_memo.cpp")

target_compile_options(VEC_SYCL_CPU PUBLIC ${SYCL_CPU_FLAGS})
target_compile_options(VEC_SYCL_GPU PUBLIC ${SYCL_GPU_FLAGS})

target_link_options(VEC_SYCL_CPU PUBLIC ${SYCL_CPU_FLAGS})
target_link_options(VEC_SYCL_GPU PUBLIC ${SYCL_GPU_FLAGS})

target_link_libraries(VEC_SCAL PRIVATE TBB::tbb)

target_link_libraries(VEC_SYCL_CPU PRIVATE TBB::tbb sycl)
target_link_libraries(VEC_SYCL_GPU PRIVATE TBB::tbb sycl)

set_property(TARGET VEC_SYCL_CPU PROPERTY CUDA_SEPARABLE_COMPILATION ON)
set_property(TARGET VEC_SYCL_GPU PROPERTY CUDA_SEPARABLE_COMPILATION ON)

install(TARGETS VEC_SCAL DESTINATION "bin/Example_1")
install(TARGETS VEC_SYCL_CPU VEC_SYCL_GPU DESTINATION "bin/Example_2")