#	
#/*****************************************************
#*                                                    *
#*  Copyright (c) 2016 Trevor Mellon                  *
#*  For further information contact t@jno.io          *
#*                                                    *
#*  Licensed under the BSD 3-clause license           *
#*  See LICENCE file for more information             *
#*                                                    *
#******************************************************/


cmake_minimum_required (VERSION 2.8)

project (ttscmd)

add_definitions(-DBOOST_ALL_NO_LIB)

option(BUILD_UNICODE ON)
option(BUILD_DLL OFF)
option(BUILD_WITH_MT OFF)

SET(CMAKE_COLOR_MAKEFILE ON)

SET (TTS_MAJOR_VERSION 1)
SET (TTS_MINOR_VERSION 0)
SET (TTS_APP_NAME "ttscmd" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

if(BUILD_WITH_MT)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif(BUILD_WITH_MT)

include (cmake/git.cmake)

configure_file(
  ${PROJECT_SOURCE_DIR}/template/Version.h.in
  ${PROJECT_SOURCE_DIR}/include/io_jno/tts/Version.h
)

set( APPCMDA ${TTS_APP_NAME}a )
set( APPCMDU ${TTS_APP_NAME})

set( LIBA ${TTS_APP_NAME}a-static)
set( LIBU ${TTS_APP_NAME}-static)


set( DLLA ${TTS_APP_NAME}a1)
set (DLLU ${TTS_APP_NAME}1)

if(WIN32)
	if (CMAKE_BUILD_TYPE MATCHES Debug)
		set( APPCMDA ${APPCMDA}_d )
		set( APPCMDU ${APPCMDU}_d)

		set( LIBA ${LIBA}_d)
		set( LIBU ${LIBU}_d)


		set( DLLA ${DLLA}_d)
		set (DLLU ${DLLU}_d)
	endif()
endif(WIN32)

FILE( GLOB HDRS
	${PROJECT_SOURCE_DIR}/include/io.jno/tts/*
)

add_subdirectory(library)
add_subdirectory(app)

include(cmake/translate.cmake)

install(FILES ${HDRS}
	 DESTINATION include/io.jno/tts
)


