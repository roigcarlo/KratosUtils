cmake_minimum_required(VERSION 3.24)

project(Mpi-Client-Server-Itercomm CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(client "client.cpp")
add_executable(server "server.cpp")

target_link_libraries(client PUBLIC MPI::MPI_CXX)
target_link_libraries(server PUBLIC MPI::MPI_CXX)

install(TARGETS client server)