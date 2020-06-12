/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifndef TTSCMD_EXPORT__H
#define TTSCMD_EXPORT__H

#if defined(_WIN32) || defined(_WINDOWS)
#	if defined(TTS_BUILDING_DLL)
#		define TTS_EXPORT __declspec(dllexport)
#	elif defined(USING_TTS_DLL)
#		define TTS_EXPORT __declspec(dllimport)
#	else
#		define TTS_EXPORT
#	endif
#else
#		define TTS_EXPORT
#endif

#endif//TTSCMD_EXPORT__H