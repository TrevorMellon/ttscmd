message(STATUS "")
message(STATUS "${DLLU} (Unicode)")

include(../common/common.cmake)

add_definitions(-DTTS_BUILDING_DLL -DUNICODE -D_UNICODE)

add_library(${DLLU} SHARED ${srcs} ${inc})
target_link_libraries(${DLLU} ${Boost_LIBRARIES} ${ICU_LIBRARIES})

install(TARGETS  ${DLLU}
	LIBRARY DESTINATION lib/
	RUNTIME DESTINATION bin/
	ARCHIVE DESTINATION lib/
)
