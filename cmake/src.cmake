
SET (TTSCMD_INCLUDEDIR ttscmd)

SET (LIB_SRC_T
	${CMAKE_SOURCE_DIR}/src/Speech.cpp
	${CMAKE_SOURCE_DIR}/src/Voices.cpp
	${CMAKE_SOURCE_DIR}/src/VoiceManager.cpp
)

SET (LIB_INC_T
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/Export.h
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/Speech.h
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/Types.h
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/Unicode.h
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/Version.h
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/VoiceManager.h
	${CMAKE_SOURCE_DIR}/include/${TTSCMD_INCLUDEDIR}/Voices.h
)

SET (LIB_SRC ${LIB_SRC_T} ${LIB_INC_T})

SET(APP_SRC_T
	${CMAKE_SOURCE_DIR}/app/src/main.cpp
	${CMAKE_SOURCE_DIR}/app/src/Application.cpp
)

SET(APP_INC_T
	${CMAKE_SOURCE_DIR}/app/include/Application.h
)

SET (APPINCDIR
	${CMAKE_SOURCE_DIR}/app/include
)

SET(APP_SOURCES ${APP_SRC_T} ${APP_INC_T})


