/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/


#ifndef TTSCMD_VOICES_H
#define TTSCMD_VOICES_H


#include <string>
#include <vector>

#include <ttscmd/Export.h>
#include <ttscmd/Unicode.h>
#include <ttscmd/Types.h>

#include <boost/locale.hpp>

namespace io_jno
{
	namespace tts
	{

		class VoiceManagerPrivate;

		class TTS_EXPORT VoiceManager
		{
		public:
			VoiceManager();
			~VoiceManager();
		public:
			bool refresh();
		public:
			const types::Voices get(const types::VoiceAttributes *like = nullptr, bool fuzzy = true);
		public:
			tts::string json(const types::Voices &v);
			tts::string json(const types::VoiceAttributes *like = nullptr, bool fuzzy = true);
		public:
			void setFuzzySplit(tts::string split);
		private:
			VoiceManagerPrivate *_p;
		};
	}
}
#endif // TTSCMD_VOICES_H