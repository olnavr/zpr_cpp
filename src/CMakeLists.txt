add_executable(system_monitor "") #deklaracja programu/projektu przekazywana w glab cmake'owego source tree

if(WIN32)
	add_subdirectory(windows)
endif()

if(UNIX)
	add_subdirectory(linux)
endif()

add_library(LIBUV_LIBRARIES SHARED IMPORTED)

if(EXISTS ${CASS_CPP_ROOT_DIR})
	set(CASS_CPP_INCLUDE_DIR "${CASS_CPP_ROOT_DIR}/include")
	add_library(CASS_CPP_LIBRARIES SHARED IMPORTED)

else(EXISTS ${CASS_CPP_ROOT_DIR})
	MESSAGE(FATAL_ERROR "cant find CASS_CPP_ROOT_DIR")
endif()

if(WIN32)
	#include and set associated with windows files
	set(LIBUV_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/dependencies/libuv/include")
	#get needed libraries's paths 
	#imported location and imported implib is probably only needed for dlls 
	set_property(TARGET CASS_CPP_LIBRARIES PROPERTY IMPORTED_LOCATION_RELEASE "${CASS_CPP_ROOT_DIR}/bin/release/cassandra.dll")
	set_property(TARGET CASS_CPP_LIBRARIES PROPERTY IMPORTED_LOCATION_DEBUG  "${CASS_CPP_ROOT_DIR}/bin/debug/cassandra.dll")
	
	set_property(TARGET CASS_CPP_LIBRARIES PROPERTY IMPORTED_IMPLIB_RELEASE "${CASS_CPP_ROOT_DIR}/lib/release/cassandra.lib")
    set_property(TARGET CASS_CPP_LIBRARIES PROPERTY IMPORTED_IMPLIB_DEBUG "${CASS_CPP_ROOT_DIR}/lib/debug/cassandra.lib")
		
	set_property(TARGET LIBUV_LIBRARIES PROPERTY IMPORTED_LOCATION_RELEASE "${LIBUV_ROOT_DIR}/lib/release/libuv.dll")
    set_property(TARGET LIBUV_LIBRARIES PROPERTY IMPORTED_LOCATION_DEBUG "${LIBUV_ROOT_DIR}/lib/debug/libuv.dll")
	
	set_property(TARGET LIBUV_LIBRARIES PROPERTY IMPORTED_IMPLIB_RELEASE "${LIBUV_ROOT_DIR}/lib/release/libuv.lib")
    set_property(TARGET LIBUV_LIBRARIES PROPERTY IMPORTED_IMPLIB_DEBUG "${LIBUV_ROOT_DIR}/lib/debug/libuv.lib")

	add_custom_command(TARGET system_monitor POST_BUILD 
         COMMAND ${CMAKE_COMMAND} -E copy_if_different
         $<$<NOT:$<CONFIG:Debug>>:${LIBUV_ROOT_DIR}/lib/release/libuv.dll>
		 $<$<CONFIG:Debug>:${LIBUV_ROOT_DIR}/lib/debug/libuv.dll>
         $<TARGET_FILE_DIR:system_monitor>)
		  
	add_custom_command(TARGET system_monitor POST_BUILD 
         COMMAND ${CMAKE_COMMAND} -E copy_if_different
         $<$<NOT:$<CONFIG:Debug>>:${CASS_CPP_ROOT_DIR}/bin/release/cassandra.dll>
		 $<$<CONFIG:Debug>:${CASS_CPP_ROOT_DIR}/bin/debug/cassandra.dll>
         $<TARGET_FILE_DIR:system_monitor>)
		 
	cotire(system_monitor)
endif()

add_subdirectory(os-independent)

target_include_directories(system_monitor PUBLIC "${CASS_CPP_INCLUDE_DIR}")
target_include_directories(system_monitor PUBLIC "${Boost_INCLUDE_DIR}")
target_include_directories(system_monitor PUBLIC "${LIBUV_INCLUDE_DIR}")

#link here as u cant use target_link_libraries in cmakelists added by add_subdirectory when executable/library is created in another cmakelist file.
target_link_libraries(system_monitor PUBLIC ${Boost_LIBRARIES})
target_link_libraries(system_monitor PUBLIC LIBUV_LIBRARIES)
target_link_libraries(system_monitor PUBLIC OpenSSL::SSL)
target_link_libraries(system_monitor PUBLIC CASS_CPP_LIBRARIES)

if(WIN32)
	string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

install(TARGETS system_monitor RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin") 