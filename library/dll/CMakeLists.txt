message(STATUS "")
message(STATUS "${DLLA} (Ascii)")

include(../common/common.cmake)

add_definitions(-DTTS_BUILDING_DLL)

add_library(${DLLA} SHARED ${srcs} ${inc})
target_link_libraries(${DLLA} ${Boost_LIBRARIES} ${ICU_LIBRARIES})

install(TARGETS  ${DLLA}
	LIBRARY DESTINATION lib/
	RUNTIME DESTINATION bin/
	ARCHIVE DESTINATION lib/
)
