
SET( srcs 
	${PROJECT_SOURCE_DIR}/src/Voices.cpp
	${PROJECT_SOURCE_DIR}/src/Speech.cpp
)

SET( inc 
	${PROJECT_SOURCE_DIR}/include/io.jno/tts/Voices.h
	${PROJECT_SOURCE_DIR}/include/io.jno/tts/Speech.h
)


SET(Boost_USE_STATIC_LIBS   ON)
find_package(Boost REQUIRED COMPONENTS locale)
find_package(ICU OPTIONAL_COMPONENTS uc data i18n)

if(Boost_FOUND)
	add_definitions(-DUSING_BOOST)
	include_directories(${Boost_INCLUDE_DIRS})
endif(Boost_FOUND)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(rapidjson)
if(RAPIDJSON_FOUND)
	include_directories(${RAPIDJSON_INCLUDE_DIRS})
	add_definitions(-DUSING_RAPIDJSON)
endif(RAPIDJSON_FOUND)