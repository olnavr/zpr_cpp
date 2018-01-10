set(OHM_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/openhardwaremonitorlib)
set(OHM_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/openhardwaremonitorlib PARENT_SCOPE)
set(MSVC_COVERAGE_COMPILE_FLAGS "${MSVC_COVERAGE_COMPILE_FLAGS} /clr")
set(MSVC_COVERAGE_LINK_FLAGS /AI"${OHM_DIR}")#ustawianie odpowiednich flag kompilatora

add_library(ohm MODULE IMPORTED)
set_property(TARGET ohm PROPERTY IMPORTED_LOCATION ${OHM_DIR}/OpenHardwareMonitorLib.dll)#
set_property(TARGET ohm PROPERTY HintPath ${OHM_DIR})

set(TARGET_NAME system_monitor) #nazwa .exe i nazwa projektu w VS

set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_CURRENT_LIST_DIR}/stdafx.h")
target_sources(${TARGET_NAME} PUBLIC 
	"${CMAKE_CURRENT_LIST_DIR}/stdafx.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Element.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Element.h"
    "${CMAKE_CURRENT_LIST_DIR}/Exception.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Exception.h"
    "${CMAKE_CURRENT_LIST_DIR}/Ohm.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Ohm.h"
    "${CMAKE_CURRENT_LIST_DIR}/Visitor.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Visitor.h"
    "${CMAKE_CURRENT_LIST_DIR}/WmiFunctor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WmiFunctor.h")
	
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "${MSVC_COVERAGE_COMPILE_FLAGS} ${MSVC_COVERAGE_LINK_FLAGS}")
set_target_properties(${TARGET_NAME} PROPERTIES VS_DOTNET_REFERENCE_ohm "${OHM_DIR}/OpenHardwareMonitorLib.dll")
set_target_properties(${TARGET_NAME} PROPERTIES VS_DOTNET_REFERENCES "System")

#TODO: MOVE UNNECESSARY FILES TO PRIVATE INTERFACE
set_source_files_properties(
        ${SOURCE_FILES}
        PROPERTIES LANGUAGE CXX
)

	
	

  