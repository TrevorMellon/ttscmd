/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifndef TTSCMD_SPEECH_H
#define TTSCMD_SPEECH_H

#include <string>

#include <ttscmd/Types.h>
#include <ttscmd/Export.h>

namespace io_jno
{
	namespace tts
	{
		class SpeechPrivate;

		class TTS_EXPORT Speech
		{
		public:
			Speech();
			~Speech();
		public:
			bool speak(tts::string say);
			bool wav(tts::string say, tts::string wavfile);
		public:
			void setVoice(types::Voice &vc);
		private:
			SpeechPrivate *_p;

		};
	}
}

#endif//TTSCMD_SPEECH_H