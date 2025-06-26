cmake_minimum_required(VERSION 3.25)

project(TensorView CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

include(FetchContent)

# Add Range-v3
FetchContent_Declare(
  range_v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  GIT_TAG        0.12.0  # or latest known stable tag
)

FetchContent_MakeAvailable(range_v3)

include_directories(include)

add_executable(TensorView "src/main.cpp")
target_link_libraries(TensorView PRIVATE range-v3)

install(TARGETS TensorView DESTINATION "bin/")