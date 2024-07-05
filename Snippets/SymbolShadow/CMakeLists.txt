project(template-organization CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("unit1")
include_directories("unit2")
include_directories("common")

add_subdirectory("unit1")
add_subdirectory("unit2")

add_executable(SymbolShadow12 "main.cpp")
add_executable(SymbolShadow21 "main.cpp")

target_link_libraries(SymbolShadow12 PUBLIC unit1 unit2)
target_link_libraries(SymbolShadow21 PUBLIC unit2 unit1)