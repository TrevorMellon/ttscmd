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


find_program(XGETTEXT xgettext)
message(${XGETTEXT})

if(XGETTEXT)

	message(STATUS "Translations")
	message(STATUS "============")
	
	SET(ARG1
		"\"src\" -iname \"*.cpp\" > \"libclutts.list\""
	)

	file(GLOB LIBFILES src/*.cpp include/clu/tts/*.h)

	file(GLOB APPFILES app/src/*.cpp)



	execute_process(
		COMMAND xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t -C -o appcmd.pot --package-name=ttscmd --msgid-bugs-address=t@jno.io ${APPFILES} ${LIBFILES}
		COMMAND xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t -C -o dll.pot --package-name=ttscmd1ib --msgid-bugs-address=t@jno.io ${LIBFILES}
	)

	file(GLOB TRANSAPP translate/appcmd/*.po)

	SET(TRANSAPPOUTDIR ${CMAKE_BINARY_DIR}/bin/translate/ttscmd/)

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

	SET(LC "/share/locale/fr/LC_MESSAGES/")
	SET(LCMSG "${CMAKE_BINARY_DIR}${LC}")
	
	file(MAKE_DIRECTORY ${LCMSG})
	file(COPY ${TRANSAPPOUTDIR}/fr.mo DESTINATION ${CMAKE_BINARY_DIR})
	file(RENAME ${CMAKE_BINARY_DIR}/fr.mo ${LCMSG}/ttscmd.mo)

	SET(LCMSG "${CMAKE_BINARY_DIR}/share/locale/fr_FR/LC_MESSAGES/")
	file(MAKE_DIRECTORY ${LCMSG})
	file(COPY ${TRANSAPPOUTDIR}/fr.mo DESTINATION ${CMAKE_BINARY_DIR})
	file(RENAME ${CMAKE_BINARY_DIR}/fr.mo ${LCMSG}/ttscmd.mo)
	
	install(DIRECTORY "${CMAKE_BINARY_DIR}/share" DESTINATION ${CMAKE_INSTALL_PREFIX})
else(XGETTEXT)
	message(STATUS "-- xgettext not found")
	message(STATUS "   Translations Disabled")
endif(XGETTEXT)

message(STATUS "")
message(STATUS "")