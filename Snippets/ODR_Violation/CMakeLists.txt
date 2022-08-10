project(template-organization CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("unit1")
include_directories("unit2")
include_directories("unit3")

add_subdirectory("unit1")
add_subdirectory("unit2")
add_subdirectory("unit3")

add_executable(TestODR1__ "main.cpp")
add_executable(TestODR12_ "main.cpp")
add_executable(TestODR1_3 "main.cpp")
add_executable(TestODR123 "main.cpp")

add_executable(TestODR132 "main.cpp")

target_link_libraries(TestODR1__ PUBLIC unit1)
target_link_libraries(TestODR12_ PUBLIC unit1 unit2)
target_link_libraries(TestODR1_3 PUBLIC unit1 unit3)
target_link_libraries(TestODR123 PUBLIC unit1 unit2 unit3)

target_link_libraries(TestODR132 PUBLIC unit1 unit3 unit2)