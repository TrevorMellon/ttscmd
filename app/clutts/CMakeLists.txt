message(STATUS "")
message(STATUS "${APPCMDA} (Ascii)")

include_directories(${PROJECT_SOURCE_DIR}/include)

SET(Boost_USE_STATIC_LIBS   ON)
find_package(Boost COMPONENTS program_options locale system thread)
find_package(ICU REQUIRED uc data i18n)

if(Boost_FOUND)
	add_definitions(-DUSING_BOOST)
	include_directories(${Boost_INCLUDE_DIRS})

	add_executable(${APPCMDA} ${PROJECT_SOURCE_DIR}/app/src/main.cpp)

	target_link_libraries(${APPCMDA} ${LIBA} ${Boost_LIBRARIES} ${ICU_LIBRARIES})

	install(TARGETS ${APPCMDA} DESTINATION bin/ )
endif(Boost_FOUND)