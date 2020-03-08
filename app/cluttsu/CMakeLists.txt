message(STATUS "")
message(STATUS "${APPCMDU} (Unicode)")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/app/include)

SET(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost COMPONENTS program_options locale system thread filesystem)
find_package(ICU OPTIONAL_COMPONENTS uc data i18n)

SET(SOURCES ${PROJECT_SOURCE_DIR}/app/src/main.cpp
	${PROJECT_SOURCE_DIR}/app/src/Application.cpp
	${PROJECT_SOURCE_DIR}/app/include/Application.h
)


if(Boost_FOUND)
	add_definitions(-DUSING_BOOST -DUNICODE -D_UNICODE)
	include_directories(${Boost_INCLUDE_DIRS})

	add_executable(${APPCMDU} ${SOURCES})

	target_link_libraries(${APPCMDU} ${LIBU} ${Boost_LIBRARIES} ${ICU_LIBRARIES})

	install(TARGETS ${APPCMDU} DESTINATION bin/ )
endif(Boost_FOUND)