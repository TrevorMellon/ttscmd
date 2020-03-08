message(STATUS "")
message(STATUS "${APPCMDA} (Ascii)")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/app/include)

SET(Boost_USE_STATIC_LIBS   OFF)
SET(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS program_options locale regex system thread filesystem)
find_package(ICU OPTIONAL_COMPONENTS uc data i18n)

SET(SOURCES ${PROJECT_SOURCE_DIR}/app/src/main.cpp
	${PROJECT_SOURCE_DIR}/app/src/Application.cpp
	${PROJECT_SOURCE_DIR}/app/include/Application.h
)

if(Boost_FOUND)
	add_definitions(-DUSING_BOOST)
	include_directories(${Boost_INCLUDE_DIRS})

	add_executable(${APPCMDA} ${SOURCES})

	target_link_libraries(${APPCMDA} ${Boost_LIBRARIES} ${LIBA}  ${ICU_LIBRARIES})
	
	target_include_directories(${APPCMDA} PUBLIC ${Boost_INCLUDE_DIRS})

	install(TARGETS ${APPCMDA} DESTINATION bin/ )
endif(Boost_FOUND)