cmake_minimum_required(VERSION 2.8)

# Finding and including BOOST library
set(Boost_USE_STATIC_LIBS   OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_REALPATH          ON)

# Mpi
find_package(MPI REQUIRED)

# Finding and including PYTHON
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})

# Select python3 by default unless its specified in the configure file
set(BOOST_PYTHON_SUFFIX "3")

message("Using component: python${BOOST_PYTHON_SUFFIX}")
if(BOOST_PYTHON_SUFFIX)
  find_package(Boost COMPONENTS "python${BOOST_PYTHON_SUFFIX}" REQUIRED)
else(BOOST_PYTHON_SUFFIX)
  find_package(Boost COMPONENTS python REQUIRED)
endif(BOOST_PYTHON_SUFFIX)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set( MPI_PROXY_SORUCES mpiProxy.cpp mpiProxyWrapper.cpp )

add_library(MpiProxy SHARED ${MPI_PROXY_SORUCES})
set_target_properties( MpiProxy PROPERTIES OUTPUT_NAME mpiProxy)
set_target_properties( MpiProxy PROPERTIES PREFIX "")

target_link_libraries(MpiProxy ${Boost_LIBRARIES} ${MPI_LIBRARIES})

install(TARGETS MpiProxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
