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

find_program(XGET xgettext)

if(NOT XGET)
	message(STATUS "-- xgettext not found, translation parsing disabled" )
else(NOT XGET)

	message(STATUS "Translations")
	message(STATUS "============")


	SET(ARG1
		"\"src\" -iname \"*.cpp\" > \"libclutts.list\""
	)

	file(GLOB LIBFILES src/*.cpp include/io_jno/tts/*.h)

	file(GLOB APPFILES app/src/*.cpp app/include/*.h)



	execute_process(
		COMMAND xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t -C -o appcmd.pot --package-name=ttscmd-1.0 --msgid-bugs-address=t@jno.io ${APPFILES} ${LIBFILES}
		COMMAND xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t -C -o dll.pot --package-name=ttscmd1-1.0 --msgid-bugs-address=t@jno.io ${LIBFILES}
	)

	file(GLOB TRANSAPP translate/ttscmd/*.po)

	SET(TRANSAPPOUTDIR ${CMAKE_BINARY_DIR}/bin/translate/ttscmd)

	file(MAKE_DIRECTORY ${TRANSAPPOUTDIR})

	foreach(TRANSX ${TRANSAPP})
		
		get_filename_component(T ${TRANSX} NAME_WE)
		
		
		SET(COMPILETRANSFILE
			${TRANSAPPOUTDIR}/${T}.mo
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



	file(GLOB MOFILES ${TRANSAPPOUTDIR}/*.mo)

	foreach(F ${MOFILES})
		
		get_filename_component(T ${F} NAME_WE)
		message(STATUS "Mo: ${T}")
		SET(LCMSG "${CMAKE_BINARY_DIR}/share/locale/${T}/LC_MESSAGES/")
		message(STATUS "Moved to ${LCMSG}ttscmd.mo")
		file(MAKE_DIRECTORY ${LCMSG})	
		
		FILE(COPY ${F} DESTINATION "${LCMSG}")
		FILE(RENAME ${LCMSG}/${T}.mo ${LCMSG}/ttscmd.mo)
	file(MAKE_DIRECTORY ${LCMSG})
	endforeach(F ${MOFILES})

	SET(PP "${CMAKE_BINARY_DIR}/share/locale/fr_FR/LC_MESSAGES/")
	FILE(MAKE_DIRECTORY ${PP})
	FILE(COPY ${TRANSAPPOUTDIR}/fr.mo DESTINATION ${PP})
	FILE(RENAME ${PP}/fr.mo ${PP}/ttscmd.mo)
	
	SET(PP "${CMAKE_BINARY_DIR}/share/locale/ru_RU/LC_MESSAGES/")
	FILE(MAKE_DIRECTORY ${PP})
	FILE(COPY ${TRANSAPPOUTDIR}/ru.mo DESTINATION ${PP})
	FILE(RENAME ${PP}/ru.mo ${PP}/ttscmd.mo)
	
	install(DIRECTORY ${CMAKE_BINARY_DIR}/share DESTINATION "/")
endif(NOT XGET)
message(STATUS "")
message(STATUS "")