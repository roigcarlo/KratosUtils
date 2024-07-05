project(template-organization CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("../common")

add_library(unit2 SHARED "library.cpp")