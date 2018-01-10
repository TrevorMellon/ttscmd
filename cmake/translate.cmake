#
#/*****************************************************
#*                                                    *
#*  Copyright (c) 2016 Trevor Mellon                  *
#*  For further information contact t@jno.io          *
#*                                                    *
#*  Licensed under the BSD 3-clause license           *
#*  See LICENCE file for more information             *
#*                                                    *
#******************************************************/
#

message(STATUS "")
message(STATUS "Translations")
message(STATUS "============")


SET(ARG1
	"\"src\" -iname \"*.cpp\" > \"libclutts.list\""
)

file(GLOB LIBFILES src/*.cpp include/clu/tts/*.h)

file(GLOB APPFILES app/src/*.cpp)



execute_process(
	COMMAND xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t -C -o appcmd.pot --package-name=clutts --msgid-bugs-address=clu@tron.rocks ${APPFILES} ${LIBFILES}
	COMMAND xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t -C -o dll.pot --package-name=clutts1 --msgid-bugs-address=clu@tron.rocks ${LIBFILES}
)

file(GLOB TRANSAPP translate/appcmd/*.po)

SET(TRANSAPPOUTDIR ${CMAKE_BINARY_DIR}/bin/translate/clutts/)

file(MAKE_DIRECTORY ${TRANSAPPOUTDIR})

foreach(TRANSX ${TRANSAPP})
	
	get_filename_component(T ${TRANSX} NAME_WE)
	
	
	SET(COMPILETRANSFILE
		${TRANSAPPOUTDIR}${T}.mo
	)
	#message(STATUS ${TRANSX})
	message(STATUS "Found app translation for language ${T}")
	message(STATUS "Creating translation: ")
	message(STATUS ${COMPILETRANSFILE})
	
	execute_process(
		COMMAND msgfmt -o ${COMPILETRANSFILE} ${TRANSX}
	)
endforeach(TRANSX ${TRANSAPP})

#manual

SET(LCMSG "${CMAKE_BINARY_DIR}/share/locale/fr/LC_MESSAGES/")
file(MAKE_DIRECTORY ${LCMSG})
file(COPY ${TRANSAPPOUTDIR}/fr.mo DESTINATION ${CMAKE_BINARY_DIR})
file(RENAME ${CMAKE_BINARY_DIR}/fr.mo ${LCMSG}/clutts.mo)

SET(LCMSG "${CMAKE_BINARY_DIR}/share/locale/fr_FR/LC_MESSAGES/")
file(MAKE_DIRECTORY ${LCMSG})
file(COPY ${TRANSAPPOUTDIR}/fr.mo DESTINATION ${CMAKE_BINARY_DIR})
file(RENAME ${CMAKE_BINARY_DIR}/fr.mo ${LCMSG}/clutts.mo)

message(STATUS "")
message(STATUS "")