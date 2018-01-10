message(STATUS "")
message(STATUS "${LIBU} (Unicode)")

include(../common/common.cmake)

add_definitions(-DUNICODE -D_UNICODE)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${LIBU} STATIC ${srcs} ${inc})

install(TARGETS ${LIBU}
	LIBRARY DESTINATION lib/
	RUNTIME DESTINATION bin/
	ARCHIVE DESTINATION lib/
)
