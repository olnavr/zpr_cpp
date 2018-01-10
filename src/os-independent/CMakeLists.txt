target_sources(system_monitor PUBLIC  
	"${CMAKE_CURRENT_LIST_DIR}/main.cpp" 
	"${CMAKE_CURRENT_LIST_DIR}/Container.cpp" 
	"${CMAKE_CURRENT_LIST_DIR}/Container.h"
	"${CMAKE_CURRENT_LIST_DIR}/CassServer.cpp" 
	"${CMAKE_CURRENT_LIST_DIR}/CassServer.h")
target_include_directories(system_monitor PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
