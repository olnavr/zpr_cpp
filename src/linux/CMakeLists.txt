set(LINUX_DIR ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(system_monitor PUBLIC ${LINUX_DIR})
file(GLOB SOURCES "${LINUX_DIR}/*.cpp")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall") 
target_sources(system_monitor PRIVATE ${SOURCES})

