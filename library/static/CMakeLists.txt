message(STATUS "")
message(STATUS "${LIBA} (Ascii)")

include(../common/common.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${LIBA} STATIC ${srcs} ${inc})

install(TARGETS ${LIBA} 
	LIBRARY DESTINATION lib/
	RUNTIME DESTINATION bin/
	ARCHIVE DESTINATION lib/
)

target_link_libraries(${LIBA} ${Boost_LIBRARIES})
