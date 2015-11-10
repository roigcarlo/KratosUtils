cmake_minimum_required(VERSION 2.8)

## Set the soruces:
set( CORE_SOURCES core.cpp )
set( APP1_SOURCES app1.cpp )
set( APP2_SOURCES app2.cpp )
set( TEST_ALL test_all.cpp )
set( TEST_CORE test_core.cpp )
set( TEST_APP1 test_app1.cpp )
set( TEST_APP2 test_app2.cpp )

add_library(Core SHARED ${CORE_SOURCES})
add_library(App1 SHARED ${APP1_SOURCES})
add_library(App2 SHARED ${APP2_SOURCES})

set_target_properties(Core PROPERTIES COMPILE_DEFINITIONS "EXPORT_CORE=1")
set_target_properties(App1 PROPERTIES COMPILE_DEFINITIONS "EXPORT_APP1=1")
set_target_properties(App2 PROPERTIES COMPILE_DEFINITIONS "EXPORT_APP2=1")

target_link_libraries(App1 Core)
target_link_libraries(App2 App1 Core)

add_executable(test_all ${TEST_ALL})
add_executable(test_core ${TEST_CORE})
add_executable(test_app1 ${TEST_APP1})
add_executable(test_app2 ${TEST_APP2})

target_link_libraries(test_all App2 App1 Core)
target_link_libraries(test_core Core)
target_link_libraries(test_app1 App1 Core)
target_link_libraries(test_app2 App2 App1 Core)

install(TARGETS test_all test_core test_app1 test_app2 Core App1 App2 DESTINATION . )
