
message(STATUS "")
message(STATUS "Applications")
message(STATUS "============")

add_subdirectory(clutts)
if(BUILD_UNICODE)
	add_subdirectory(cluttsu)
endif(BUILD_UNICODE)