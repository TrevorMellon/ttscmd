SET(Boost_USE_STATIC_LIBS   OFF)
#SET(Boost_USE_MULTITHREADED OFF)

find_package(Boost COMPONENTS program_options locale regex system thread filesystem)

find_package(ICU OPTIONAL_COMPONENTS uc data i18n)

include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB=1 -DBOOST_ALL_DYN_LINK=1)
add_definitions(-DUSING_BOOST=1)
include_directories(${ICU_INCLUDE_DIRS})

SET(LIBRARIES ${Boost_LIBRARIES} ${ICU_LIBRARIES})