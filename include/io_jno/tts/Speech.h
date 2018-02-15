/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifndef TTSCMD_SPEECH_H
#define TTSCMD_SPEECH_H

#include <string>

#include <io_jno/tts/Types.h>

namespace io_jno
{
	namespace tts
	{
		class SpeechPrivate;

		class Speech
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