message(STATUS "")
message(STATUS "Libraries")
message(STATUS "=========")

message(STATUS "")
message(STATUS "Shared")
if(BUILD_DLL)
	add_subdirectory(${PROJECT_SOURCE_DIR}/library/dll)
	
	if(BUILD_UNICODE)
		add_subdirectory(${PROJECT_SOURCE_DIR}/library/dllunicode)
		
	endif(BUILD_UNICODE)
endif(BUILD_DLL)

message(STATUS "")
message(STATUS "Static")

add_subdirectory(${PROJECT_SOURCE_DIR}/library/static)

if(BUILD_UNICODE)
	add_subdirectory(${PROJECT_SOURCE_DIR}/library/staticunicode)
endif(BUILD_UNICODE)