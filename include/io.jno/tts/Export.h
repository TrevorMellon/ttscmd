/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifndef TTSCMD_EXPORT__H
#define TTSCMD_EXPORT__H

#if defined(_WIN32) || defined(_WINDOWS)
#	if defined(CLU_TTS_BUILDING_DLL)
#		define CLU_s_TTS_EXPORT __declspec(dllexport)
#	elif defined(USING_CLU_s_TTS_DLL)
#		define CLU_s_TTS_EXPORT __declspec(dllimport)
#	else
#		define CLU_s_TTS_EXPORT
#	endif
#else
#		define CLU_s_TTS_EXPORT
#endif

#endif//TTSCMD_EXPORT__H