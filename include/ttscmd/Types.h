/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifndef TTSCMD_TYPES_H
#define TTSCMD_TYPES_H

#include <string>
#include <vector>

#include <boost/locale.hpp>

#include <ttscmd/Unicode.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdint.h>

namespace io_jno
{
	namespace tts
	{
		namespace types
		{
			struct LangItem
			{
				WORD id;
				tts::string name;
			};

			enum class VoiceAgeE
			{
				UNKNOWN = 0,
				Child,
				Teen,
				Adult,
				Senior
			};

			enum class VoiceGenderE
			{
				UNKNOWN = 0,
				Male,
				Female
			};

			struct VoiceAge
			{
				VoiceAgeE age;

				void zero()
				{
					age = VoiceAgeE::UNKNOWN;
				}

				tts::string toAgeStr()
				{
					std::wstring wstr;
					tts::string out;

					if (age == VoiceAgeE::UNKNOWN)
						wstr.clear();
					else if (age == VoiceAgeE::Child)
						wstr = boost::locale::translate(L"Child").str();
					else if (age == VoiceAgeE::Teen)
						wstr = boost::locale::translate(L"Teenager").str();
					else if (age == VoiceAgeE::Adult)
						wstr = boost::locale::translate(L"Adult").str();
					else if (age == VoiceAgeE::Senior)
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
						age = VoiceAgeE::Child;
					else if (s == boost::locale::translate(L"teen").str()
						|| s == boost::locale::translate(L"teens").str()
						|| s == boost::locale::translate(L"teenager").str()
						|| s == boost::locale::translate(L"teenagers").str()
						|| s == boost::locale::translate(L"Teen").str()
						|| s == boost::locale::translate(L"Teens").str()
						|| s == boost::locale::translate(L"Teenager").str()
						|| s == boost::locale::translate(L"Teenagers").str()
						)
						age = VoiceAgeE::Teen;
					else if (s == boost::locale::translate(L"adult").str()
						|| s == boost::locale::translate(L"adults").str()
						|| s == boost::locale::translate(L"Adult").str()
						|| s == boost::locale::translate(L"Adults").str()
						)
						age = VoiceAgeE::Adult;
					else if (s == boost::locale::translate(L"senior").str()
						|| s == boost::locale::translate(L"seniors").str()
						|| s == boost::locale::translate(L"old").str()
						|| s == boost::locale::translate(L"Senior").str()
						|| s == boost::locale::translate(L"Seniors").str()
						|| s == boost::locale::translate(L"Old").str()
						)
						age = VoiceAgeE::Senior;
					else
						age = VoiceAgeE::UNKNOWN;
				}
			};

			struct VoiceGenderZ
			{
				VoiceGenderE gender;

				void zero()
				{
					gender = VoiceGenderE::UNKNOWN;
				}

				tts::string toGenderStr()
				{

					std::wstring tempstr;
					if (gender == VoiceGenderE::UNKNOWN)
					{
						tempstr = L"";
						return tts::string(tempstr.begin(), tempstr.end());
					}
					else if (gender == VoiceGenderE::Male)
					{
						tempstr = boost::locale::translate(L"Male").str();
						return tts::string(tempstr.begin(), tempstr.end());
					}
					else if (gender == VoiceGenderE::Female)
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
						gender = VoiceGenderE::Male;
					else if (tempstr == boost::locale::translate(L"female").str()
						|| tempstr == boost::locale::translate(L"Female").str()
						|| tempstr == boost::locale::translate(L"females").str()
						|| tempstr == boost::locale::translate(L"Females").str()
						|| tempstr == boost::locale::translate(L"gender", L"f").str()
						)
						gender = VoiceGenderE::Female;
					else
						gender = VoiceGenderE::UNKNOWN;
				}
			};

			struct VoiceAttributes : public VoiceAge, VoiceGenderZ
			{
				tts::string		language;
				tts::string		name;
				tts::string		vendor;
				tts::string		languageCode;

				void zero()
				{
					age = VoiceAgeE::UNKNOWN;
					gender = VoiceGenderE::UNKNOWN;

					std::wstring tstr = L"";

					language = tts::string(tstr.begin(), tstr.end());
					name = tts::string(tstr.begin(), tstr.end());
					vendor = tts::string(tstr.begin(), tstr.end());

				}
			};

			struct Voice
			{

				tts::string			classid;
				tts::string		tokenlocation;

				VoiceAttributes	attributes;

				void zero()
				{
					std::wstring tstr = L"";
					classid = tts::string(tstr.begin(), tstr.end());
					tokenlocation = tts::string(tstr.begin(), tstr.end());
					attributes.zero();
				}
			};

			typedef std::vector<Voice> Voices;

		}//namespace types
	}//namespace tts
}//namespace io_jno

#endif//TTSCMD_TYPES_H