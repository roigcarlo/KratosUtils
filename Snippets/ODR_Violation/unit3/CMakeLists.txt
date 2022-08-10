project(template-organization CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("${CMAKE_SOURCE_DIR}")

add_library(unit3 SHARED "class_instantiation.cpp")
target_link_libraries(unit3 unit1)