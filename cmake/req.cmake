
SET(Boost_USE_STATIC_LIBS   OFF)
SET(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS program_options locale regex system thread filesystem)

find_package(ICU OPTIONAL_COMPONENTS uc data i18n)

include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DUSING_BOOST=1)
include_directories(${ICU_INCLUDE_DIRS})

SET(LIBRARIES ${Boost_LIBRARIES} ${ICU_LIBRARIES})