cmake_minimum_required(VERSION 3.7.2)
project(system_monitor C CXX)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)
#

#set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME 	OFF)

if(UNIX)
	set(BOOST_ROOT /opt/boost_cpp/)
	include(FindLibUV)
endif(UNIX)

find_package(Boost REQUIRED)

if(WIN32)
	set(CASS_CPP_ROOT_DIR "${CMAKE_SOURCE_DIR}/src/windows/dependencies/cassandraCPP")
	set(LIBUV_ROOT_DIR "${CMAKE_SOURCE_DIR}/src/windows/dependencies/libuv")
	set(OPENSSL_ROOT_DIR "${CMAKE_SOURCE_DIR}/src/windows/dependencies/openssl")
endif()

find_package(OpenSSL REQUIRED)

option(WITH_TESTS "Build Tests" OFF)
mark_as_advanced(WITH_TESTS)
message(STATUS "Build Tests: 	${WITH_TESTS}")

if(WITH_TESTS)
	add_subdirectory(tests)
endif(WITH_TESTS)

add_subdirectory(src)

#TODO: SOURCE_GROUP
