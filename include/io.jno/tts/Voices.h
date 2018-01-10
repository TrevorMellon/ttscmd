/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/


#ifndef IO_JNO_VOICES_H
#define IO_JNO_VOICES_H

#include <windows.h>

#include <stdint.h>
#include <string>
#include <vector>

#include <io.jno/tts/Export.h>
#include <io.jno/tts/Unicode.h>

#include <boost/locale.hpp>

namespace io_jno
{
	namespace tts
	{
		struct LangItem
		{
			WORD id;
			tts::string name;
		};
		
		enum VoiceAge
		{
			VoiceAge_UNKNOWN = 0,
			VoiceAge_Child,
			VoiceAge_Teen,
			VoiceAge_Adult,
			VoiceAge_Senior
		};

		

		enum VoiceGender
		{
			VoiceGender_UNKNOWN = 0,
			VoiceGender_Male,
			VoiceGender_Female
		};


		struct VoiceAgeZ
		{
			VoiceAge age;

			void zero()
			{
				age = VoiceAge_UNKNOWN;
			}

			tts::string toAgeStr()
			{
				std::wstring wstr;
				tts::string out;
				
				if (age == VoiceAge_UNKNOWN)
					wstr.clear();
				else if (age == VoiceAge_Child)
					wstr = boost::locale::translate(L"Child").str();
				else if (age == VoiceAge_Teen)
					wstr = boost::locale::translate(L"Teenager").str();
				else if (age == VoiceAge_Adult)
					wstr = boost::locale::translate(L"Adult").str();
				else if (age == VoiceAge_Senior)
					wstr = boost::locale::translate(L"Senior").str();
				else
					wstr.clear();

				out = tts::string(wstr.begin(), wstr.end());
				return out;
			}

			void fromAgeStr(tts::string in)
			{
				std::wstring s(in.begin(), in.end());

				if (s == boost::locale::translate(L"child").str()
					|| s == boost::locale::translate(L"children").str()
					|| s == boost::locale::translate(L"kid").str()
					|| s == boost::locale::translate(L"kids").str()
					|| s == boost::locale::translate(L"Child").str()
					|| s == boost::locale::translate(L"Children").str()
					|| s == boost::locale::translate(L"Kid").str()
					|| s == boost::locale::translate(L"Kids").str()
					)
					age = VoiceAge_Child;
				else if (s == boost::locale::translate(L"teen").str()
					|| s == boost::locale::translate(L"teens").str()
					|| s == boost::locale::translate(L"teenager").str()
					|| s == boost::locale::translate(L"teenagers").str()
					|| s == boost::locale::translate(L"Teen").str()
					|| s == boost::locale::translate(L"Teens").str()
					|| s == boost::locale::translate(L"Teenager").str()
					|| s == boost::locale::translate(L"Teenagers").str()
					)
					age = VoiceAge_Teen;
				else if (s == boost::locale::translate(L"adult").str()
					|| s == boost::locale::translate(L"adults").str()
					|| s == boost::locale::translate(L"Adult").str()
					|| s == boost::locale::translate(L"Adults").str()
					)
					age = VoiceAge_Adult;
				else if (s == boost::locale::translate(L"senior").str()
					|| s == boost::locale::translate(L"seniors").str()
					|| s == boost::locale::translate(L"old").str()
					|| s == boost::locale::translate(L"Senior").str()
					|| s == boost::locale::translate(L"Seniors").str()
					|| s == boost::locale::translate(L"Old").str()
					)
					age = VoiceAge_Senior;
				else
					age = VoiceAge_UNKNOWN;
			}
		};

		struct VoiceGenderZ
		{
			VoiceGender gender;

			void zero()
			{
				gender = VoiceGender_UNKNOWN;
			}

			tts::string toGenderStr()
			{
				
				std::wstring tempstr;
				if (gender == VoiceGender_UNKNOWN)
				{
					tempstr = L"";
					return tts::string(tempstr.begin(),tempstr.end());
				}
				else if (gender == VoiceGender_Male)
				{
					tempstr = boost::locale::translate(L"Male").str();
					return tts::string(tempstr.begin(), tempstr.end());
				}
				else if (gender == VoiceGender_Female)
				{
					tempstr = boost::locale::translate(L"Female").str();
					
				}
				else
				{
					tempstr = L"";					
				}
#if UNICODE
				return tempstr;
#else
				return tts::string(tempstr.begin(), tempstr.end());
#endif
			}

			void fromGenderStr(tts::string s)
			{
				std::wstring tempstr(s.begin(), s.end());
				
				if (tempstr == boost::locale::translate(L"male").str()
					|| tempstr == boost::locale::translate(L"Male").str()
					|| tempstr == boost::locale::translate(L"males").str()
					|| tempstr == boost::locale::translate(L"Males").str()
					|| tempstr == boost::locale::translate(L"gender", L"m").str()
					)
					gender = VoiceGender_Male;
				else if (tempstr == boost::locale::translate(L"female").str()
					|| tempstr == boost::locale::translate(L"Female").str()
					|| tempstr == boost::locale::translate(L"females").str()
					|| tempstr == boost::locale::translate(L"Females").str()
					|| tempstr == boost::locale::translate(L"gender", L"f").str()
					)
					gender = VoiceGender_Female;
				else
					gender = VoiceGender_UNKNOWN;
			}
		};

		struct VoiceAttributesZ : public VoiceAgeZ, VoiceGenderZ
		{
			tts::string		language;
			tts::string		name;
			tts::string		vendor;
			tts::string		languageCode;

			void zero()
			{
				age = VoiceAge_UNKNOWN;
				gender = VoiceGender_UNKNOWN;

				std::wstring tstr = L"";

				language = tts::string(tstr.begin(),tstr.end());
				name = tts::string(tstr.begin(), tstr.end());
				vendor = tts::string(tstr.begin(), tstr.end());

			}
		};

		struct VoiceZ
		{

			tts::string			classid;
			tts::string		tokenlocation;

			VoiceAttributesZ	attributes;

			void zero()
			{
				std::wstring tstr = L"";
				classid = tts::string(tstr.begin(), tstr.end());
				tokenlocation = tts::string(tstr.begin(), tstr.end());
				attributes.zero();
			}
		};

		typedef std::vector<VoiceZ> Voices;

		class VoicesKPrivate;

		class CLU_s_TTS_EXPORT VoicesK
		{
		public:
			VoicesK();
			~VoicesK();
		public:
			bool refresh();
		public:
			const Voices get(const VoiceAttributesZ *like = nullptr, bool fuzzy = true);
		public:
			tts::string json(const Voices &v);
			tts::string json(const VoiceAttributesZ *like = nullptr, bool fuzzy = true);
		public:
			void setFuzzySplit(tts::string split);
		private:
			VoicesKPrivate *_p;
		};


	}
}
#endif // IO_JNO_VOICES_H