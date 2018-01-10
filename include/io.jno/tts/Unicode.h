/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifndef __CLU_s_TTS_UNICODE__H_
#define __CLU_s_TTS_UNICODE__H_

#include <string>
#include <sstream>
#include <iostream>

namespace io_jno
{
	namespace tts
	{
#ifdef UNICODE
		typedef std::wstring		string;
		typedef std::wstringstream	stringstream;
		
#else
		typedef std::string			string;
		typedef std::stringstream	stringstream;
		
#endif
	}
}

#endif