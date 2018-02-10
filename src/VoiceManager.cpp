/*****************************************************
*                                                    *
*  copyright (c) 2018 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/


#include <io_jno/tts/VoiceManager.h>
#include <io_jno/tts/Version.h>
#include <io_jno/tts/Types.h>

#include <windows.h>
#include <tchar.h>
#include <sstream>

#ifdef USING_BOOST
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#endif

#ifndef FUZZY_SPLIT
# ifdef UNICODE 
#  define FUZZY_SPLIT L" "
# else
#  define FUZZY_SPLIT " "
# endif
#endif

#ifdef USING_RAPIDJSON
# include <rapidjson/rapidjson.h>
# include <rapidjson/document.h>
# include <rapidjson/stringbuffer.h>
# include <rapidjson/writer.h>
#endif

#include <codecvt>
#include <locale>

using namespace io_jno;
using namespace io_jno::tts;

namespace lo = boost::locale;

namespace io_jno{

	namespace tts{

#ifdef UNICODE
		types::LangItem PrimarayLangArray[] = {
			LANG_AFRIKAANS, lo::translate(L"Afrikaans").str(),
			LANG_ALBANIAN, lo::translate(L"Albanian").str(),
			LANG_ALSATIAN, lo::translate(L"Alsatian").str(),
			LANG_AMHARIC, lo::translate(L"Amharic").str(),
			LANG_ARABIC, lo::translate(L"Arabic").str(),
			LANG_ARMENIAN, lo::translate(L"Armenian").str(),
			LANG_ASSAMESE, lo::translate(L"Assamese").str(),
			LANG_AZERI, lo::translate(L"Azeri").str(),
			LANG_BANGLA, lo::translate(L"Bangla").str(),
			LANG_BASHKIR, lo::translate(L"Bashkir").str(),
			LANG_BASQUE, lo::translate(L"Basque").str(),
			LANG_BELARUSIAN, lo::translate(L"Belarussian").str(),
			LANG_BOSNIAN, lo::translate(L"Bosnian").str(),
			LANG_BRETON, lo::translate(L"Breton").str(),
			LANG_BULGARIAN, lo::translate(L"Bulgarian").str(),
			LANG_CENTRAL_KURDISH, lo::translate(L"Kurdish Central").str(),
			LANG_CHEROKEE, lo::translate(L"Cherokee").str(),
			LANG_CATALAN, lo::translate(L"Catalan").str(),
			LANG_CHINESE, lo::translate(L"Chinese").str(),
			LANG_CHINESE_SIMPLIFIED, lo::translate(L"Chinese Simplified").str(),
			LANG_CHINESE_TRADITIONAL, lo::translate(L"Chinese Traditional").str(),
			LANG_CORSICAN, lo::translate(L"Corsican").str(),
			LANG_CROATIAN, lo::translate(L"Croatian").str(),
			LANG_CZECH, lo::translate(L"Czech").str(),
			LANG_DANISH, lo::translate(L"Danish").str(),
			LANG_DARI, lo::translate(L"Dari").str(),
			LANG_DIVEHI, lo::translate(L"Divehi").str(),
			LANG_DUTCH, lo::translate(L"Dutch").str(),
			LANG_ENGLISH, lo::translate(L"English").str(),
			LANG_ESTONIAN, lo::translate(L"Estonian").str(),
			LANG_FAEROESE, lo::translate(L"Faeroese").str(),
			LANG_FILIPINO, lo::translate(L"Filipino").str(),
			LANG_FINNISH, lo::translate(L"Finnish").str(),
			LANG_FRENCH, lo::translate(L"French").str(),
			LANG_FRISIAN, lo::translate(L"Frisian").str(),
			LANG_GALICIAN, lo::translate(L"Galacian").str(),
			LANG_GEORGIAN, lo::translate(L"Georgian").str(),
			LANG_GERMAN, lo::translate(L"German").str(),
			LANG_GREEK, lo::translate(L"Greek").str(),
			LANG_GREENLANDIC, lo::translate(L"Greenlandic").str(),
			LANG_GUJARATI, lo::translate(L"Gujarati").str(),
			LANG_HAUSA, lo::translate(L"Hausa").str(),
			LANG_HAWAIIAN, lo::translate(L"Hawaiian").str(),
			LANG_HEBREW, lo::translate(L"Hebrew").str(),
			LANG_HINDI, lo::translate(L"Hindi").str(),
			LANG_HUNGARIAN, lo::translate(L"Hungarian").str(),
			LANG_ICELANDIC, lo::translate(L"Icelandic").str(),
			LANG_IGBO, lo::translate(L"Igbo").str(),
			LANG_INDONESIAN, lo::translate(L"Indonesian").str(),
			LANG_INUKTITUT, lo::translate(L"Inuktitut").str(),
			LANG_IRISH, lo::translate(L"Irish").str(),
			LANG_XHOSA, lo::translate(L"Xhosa").str(),
			LANG_ZULU, lo::translate(L"Zulu").str(),
			LANG_ITALIAN, lo::translate(L"Italian").str(),
			LANG_JAPANESE, lo::translate(L"Japanese").str(),
			LANG_KANNADA, lo::translate(L"Kannada").str(),
			LANG_KASHMIRI, lo::translate(L"Kashmiri").str(),
			LANG_KAZAK, lo::translate(L"Kazak").str(),
			LANG_KHMER, lo::translate(L"Khmer").str(),
			LANG_KICHE, lo::translate(L"Kiche").str(),
			LANG_KINYARWANDA, lo::translate(L"Kinyarwanda").str(),
			LANG_KONKANI, lo::translate(L"Konkani").str(),
			LANG_KOREAN, lo::translate(L"Korean").str(),
			LANG_KYRGYZ, lo::translate(L"Kyrgyz").str(),
			LANG_LAO, lo::translate(L"Lao").str(),
			LANG_LATVIAN, lo::translate(L"Latvian").str(),
			LANG_LITHUANIAN, lo::translate(L"Lithuanian").str(),
			LANG_LOWER_SORBIAN, lo::translate(L"Sorbian Lower").str(),
			LANG_LUXEMBOURGISH, lo::translate(L"Luxembourgish").str(),
			LANG_MACEDONIAN, lo::translate(L"Macedonian").str(),
			LANG_MALAY, lo::translate(L"Malay").str(),
			LANG_MALAYALAM, lo::translate(L"Malayalam").str(),
			LANG_MALTESE, lo::translate(L"Maltese").str(),
			LANG_MANIPURI, lo::translate(L"Manipuri").str(),
			LANG_MAORI, lo::translate(L"Maori").str(),
			LANG_MAPUDUNGUN, lo::translate(L"Mapudungun").str(),
			LANG_MARATHI, lo::translate(L"Marathi").str(),
			LANG_MOHAWK, lo::translate(L"Mohawk").str(),
			LANG_MONGOLIAN, lo::translate(L"Mongolian").str(),
			LANG_NEPALI, lo::translate(L"Nepali").str(),
			LANG_NORWEGIAN, lo::translate(L"Norwegian").str(),
			LANG_OCCITAN, lo::translate(L"Occitan").str(),
			LANG_ORIYA, lo::translate(L"Oriya").str(),
			LANG_PASHTO, lo::translate(L"Pashto").str(),
			LANG_PERSIAN, lo::translate(L"Persian").str(),
			LANG_POLISH, lo::translate(L"Polish").str(),
			LANG_PORTUGUESE, lo::translate(L"Portugeuse").str(),
			LANG_PULAR, lo::translate(L"Pular").str(),
			LANG_PUNJABI, lo::translate(L"Punjabi").str(),
			LANG_QUECHUA, lo::translate(L"Quechua").str(),
			LANG_ROMANIAN, lo::translate(L"Romanian").str(),
			LANG_ROMANSH, lo::translate(L"Romansh").str(),
			LANG_RUSSIAN, lo::translate(L"Russian").str(),
			LANG_SAKHA, lo::translate(L"Sakha").str(),
			LANG_SAMI, lo::translate(L"Sami").str(),
			LANG_SANSKRIT, lo::translate(L"Sanskrit").str(),
			LANG_SERBIAN, lo::translate(L"Serbian").str(),
			LANG_SOTHO, lo::translate(L"Sotho").str(),
			LANG_TSWANA, lo::translate(L"Tswana").str(),
			LANG_SINDHI, lo::translate(L"Sindhi").str(),
			LANG_SINHALESE, lo::translate(L"Sinhalese").str(),
			LANG_SLOVAK, lo::translate(L"Slovak").str(),
			LANG_SLOVENIAN, lo::translate(L"Slovenian").str(),
			LANG_SPANISH, lo::translate(L"Spanish").str(),
			LANG_SWAHILI, lo::translate(L"Swahili").str(),
			LANG_SWEDISH, lo::translate(L"Swedish").str(),
			LANG_SYRIAC, lo::translate(L"Syriac").str(),
			LANG_TAJIK, lo::translate(L"Tajik").str(),
			LANG_TAMAZIGHT, lo::translate(L"Tamazight").str(),
			LANG_TAMIL, lo::translate(L"Tamil").str(),
			LANG_TATAR, lo::translate(L"Tatar").str(),
			LANG_TELUGU, lo::translate(L"Telegu").str(),
			LANG_THAI, lo::translate(L"Thai").str(),
			LANG_TIBETAN, lo::translate(L"Tibetan").str(),
			LANG_TIGRIGNA, lo::translate(L"Tigrigna").str(),
			LANG_TURKISH, lo::translate(L"Turkish").str(),
			LANG_TURKMEN, lo::translate(L"Turkmen").str(),
			LANG_UKRAINIAN, lo::translate(L"Ukrainian").str(),
			LANG_UPPER_SORBIAN, lo::translate(L"Sorbian Upper").str(),
			LANG_URDU, lo::translate(L"URDU").str(),
			LANG_UIGHUR, lo::translate(L"Uighur").str(),
			LANG_UZBEK, lo::translate(L"Uzbek").str(),
			LANG_VALENCIAN, lo::translate(L"Valencian").str(),
			LANG_VIETNAMESE, lo::translate(L"Vietnamese").str(),
			LANG_WELSH, lo::translate(L"Welsh").str(),
			LANG_WOLOF, lo::translate(L"Wolof").str(),
			LANG_YI, lo::translate(L"Yi").str(),
			LANG_YORUBA, lo::translate(L"Yoruba").str(),
			0, L""
		};
#else
		types::LangItem PrimarayLangArray[] = {
			LANG_AFRIKAANS, lo::translate("Afrikaans").str(),
			LANG_ALBANIAN, lo::translate("Albanian").str(),
			LANG_ALSATIAN, lo::translate("Alsatian").str(),
			LANG_AMHARIC, lo::translate("Amharic").str(),
			LANG_ARABIC, lo::translate("Arabic").str(),
			LANG_ARMENIAN, lo::translate("Armenian").str(),
			LANG_ASSAMESE, lo::translate("Assamese").str(),
			LANG_AZERI, lo::translate("Azeri").str(),
			LANG_BANGLA, lo::translate("Bangla").str(),
			LANG_BASHKIR, lo::translate("Bashkir").str(),
			LANG_BASQUE, lo::translate("Basque").str(),
			LANG_BELARUSIAN, lo::translate("Belarussian").str(),
			LANG_BOSNIAN, lo::translate("Bosnian").str(),
			LANG_BRETON, lo::translate("Breton").str(),
			LANG_BULGARIAN, lo::translate("Bulgarian").str(),
			LANG_CENTRAL_KURDISH, lo::translate("Kurdish Central").str(),
			LANG_CHEROKEE, lo::translate("Cherokee").str(),
			LANG_CATALAN, lo::translate("Catalan").str(),
			LANG_CHINESE, lo::translate("Chinese").str(),
			LANG_CHINESE_SIMPLIFIED, lo::translate("Chinese Simplified").str(),
			LANG_CHINESE_TRADITIONAL, lo::translate("Chinese Traditional").str(),
			LANG_CORSICAN, lo::translate("Corsican").str(),
			LANG_CROATIAN, lo::translate("Croatian").str(),
			LANG_CZECH, lo::translate("Czech").str(),
			LANG_DANISH, lo::translate("Danish").str(),
			LANG_DARI, lo::translate("Dari").str(),
			LANG_DIVEHI, lo::translate("Divehi").str(),
			LANG_DUTCH, lo::translate("Dutch").str(),
			LANG_ENGLISH, lo::translate("English").str(),
			LANG_ESTONIAN, lo::translate("Estonian").str(),
			LANG_FAEROESE, lo::translate("Faeroese").str(),
			LANG_FILIPINO, lo::translate("Filipino").str(),
			LANG_FINNISH, lo::translate("Finnish").str(),
			LANG_FRENCH, lo::translate("French").str(),
			LANG_FRISIAN, lo::translate("Frisian").str(),
			LANG_GALICIAN, lo::translate("Galacian").str(),
			LANG_GEORGIAN, lo::translate("Georgian").str(),
			LANG_GERMAN, lo::translate("German").str(),
			LANG_GREEK, lo::translate("Greek").str(),
			LANG_GREENLANDIC, lo::translate("Greenlandic").str(),
			LANG_GUJARATI, lo::translate("Gujarati").str(),
			LANG_HAUSA, lo::translate("Hausa").str(),
			LANG_HAWAIIAN, lo::translate("Hawaiian").str(),
			LANG_HEBREW, lo::translate("Hebrew").str(),
			LANG_HINDI, lo::translate("Hindi").str(),
			LANG_HUNGARIAN, lo::translate("Hungarian").str(),
			LANG_ICELANDIC, lo::translate("Icelandic").str(),
			LANG_IGBO, lo::translate("Igbo").str(),
			LANG_INDONESIAN, lo::translate("Indonesian").str(),
			LANG_INUKTITUT, lo::translate("Inuktitut").str(),
			LANG_IRISH, lo::translate("Irish").str(),
			LANG_XHOSA, lo::translate("Xhosa").str(),
			LANG_ZULU, lo::translate("Zulu").str(),
			LANG_ITALIAN, lo::translate("Italian").str(),
			LANG_JAPANESE, lo::translate("Japanese").str(),
			LANG_KANNADA, lo::translate("Kannada").str(),
			LANG_KASHMIRI, lo::translate("Kashmiri").str(),
			LANG_KAZAK, lo::translate("Kazak").str(),
			LANG_KHMER, lo::translate("Khmer").str(),
			LANG_KICHE, lo::translate("Kiche").str(),
			LANG_KINYARWANDA, lo::translate("Kinyarwanda").str(),
			LANG_KONKANI, lo::translate("Konkani").str(),
			LANG_KOREAN, lo::translate("Korean").str(),
			LANG_KYRGYZ, lo::translate("Kyrgyz").str(),
			LANG_LAO, lo::translate("Lao").str(),
			LANG_LATVIAN, lo::translate("Latvian").str(),
			LANG_LITHUANIAN, lo::translate("Lithuanian").str(),
			LANG_LOWER_SORBIAN, lo::translate("Sorbian Lower").str(),
			LANG_LUXEMBOURGISH, lo::translate("Luxembourgish").str(),
			LANG_MACEDONIAN, lo::translate("Macedonian").str(),
			LANG_MALAY, lo::translate("Malay").str(),
			LANG_MALAYALAM, lo::translate("Malayalam").str(),
			LANG_MALTESE, lo::translate("Maltese").str(),
			LANG_MANIPURI, lo::translate("Manipuri").str(),
			LANG_MAORI, lo::translate("Maori").str(),
			LANG_MAPUDUNGUN, lo::translate("Mapudungun").str(),
			LANG_MARATHI, lo::translate("Marathi").str(),
			LANG_MOHAWK, lo::translate("Mohawk").str(),
			LANG_MONGOLIAN, lo::translate("Mongolian").str(),
			LANG_NEPALI, lo::translate("Nepali").str(),
			LANG_NORWEGIAN, lo::translate("Norwegian").str(),
			LANG_OCCITAN, lo::translate("Occitan").str(),
			LANG_ORIYA, lo::translate("Oriya").str(),
			LANG_PASHTO, lo::translate("Pashto").str(),
			LANG_PERSIAN, lo::translate("Persian").str(),
			LANG_POLISH, lo::translate("Polish").str(),
			LANG_PORTUGUESE, lo::translate("Portugeuse").str(),
			LANG_PULAR, lo::translate("Pular").str(),
			LANG_PUNJABI, lo::translate("Punjabi").str(),
			LANG_QUECHUA, lo::translate("Quechua").str(),
			LANG_ROMANIAN, lo::translate("Romanian").str(),
			LANG_ROMANSH, lo::translate("Romansh").str(),
			LANG_RUSSIAN, lo::translate("Russian").str(),
			LANG_SAKHA, lo::translate("Sakha").str(),
			LANG_SAMI, lo::translate("Sami").str(),
			LANG_SANSKRIT, lo::translate("Sanskrit").str(),
			LANG_SERBIAN, lo::translate("Serbian").str(),
			LANG_SOTHO, lo::translate("Sotho").str(),
			LANG_TSWANA, lo::translate("Tswana").str(),
			LANG_SINDHI, lo::translate("Sindhi").str(),
			LANG_SINHALESE, lo::translate("Sinhalese").str(),
			LANG_SLOVAK, lo::translate("Slovak").str(),
			LANG_SLOVENIAN, lo::translate("Slovenian").str(),
			LANG_SPANISH, lo::translate("Spanish").str(),
			LANG_SWAHILI, lo::translate("Swahili").str(),
			LANG_SWEDISH, lo::translate("Swedish").str(),
			LANG_SYRIAC, lo::translate("Syriac").str(),
			LANG_TAJIK, lo::translate("Tajik").str(),
			LANG_TAMAZIGHT, lo::translate("Tamazight").str(),
			LANG_TAMIL, lo::translate("Tamil").str(),
			LANG_TATAR, lo::translate("Tatar").str(),
			LANG_TELUGU, lo::translate("Telegu").str(),
			LANG_THAI, lo::translate("Thai").str(),
			LANG_TIBETAN, lo::translate("Tibetan").str(),
			LANG_TIGRIGNA, lo::translate("Tigrigna").str(),
			LANG_TURKISH, lo::translate("Turkish").str(),
			LANG_TURKMEN, lo::translate("Turkmen").str(),
			LANG_UKRAINIAN, lo::translate("Ukrainian").str(),
			LANG_UPPER_SORBIAN, lo::translate("Sorbian Upper").str(),
			LANG_URDU, lo::translate("URDU").str(),
			LANG_UIGHUR, lo::translate("Uighur").str(),
			LANG_UZBEK, lo::translate("Uzbek").str(),
			LANG_VALENCIAN, lo::translate("Valencian").str(),
			LANG_VIETNAMESE, lo::translate("Vietnamese").str(),
			LANG_WELSH, lo::translate("Welsh").str(),
			LANG_WOLOF, lo::translate("Wolof").str(),
			LANG_YI, lo::translate("Yi").str(),
			LANG_YORUBA, lo::translate("Yoruba").str(),
			0, ""
	};
#endif

		class VoiceManagerPrivate
		{
		public:
			VoiceManagerPrivate(VoiceManager *q)
			{
				_q = q;
				_split = FUZZY_SPLIT;
				buildLanguageTable();
			}
			~VoiceManagerPrivate()
			{
				_q = nullptr;
				v.clear();
				caseinsensitiveVoices.clear();
			}
		public:

			void buildLanguageTable()
			{
				types::LangItem li = PrimarayLangArray[0];
				int i = 0;

				while (li.id != 0
					&& !li.name.empty())
				{
					_primaryLangLUT.push_back(li);
					boost::algorithm::to_lower(li.name);
					_primaryLangLUTInsensitive.push_back(li);

					++i;
					li = PrimarayLangArray[i];					
				}
			}

			bool refresh()
			{
				caseinsensitiveVoices.clear();
				v.clear();
#ifdef UNICODE
				pollSpeechRegistry(L"SOFTWARE\\Microsoft\\Speech\\Voices");
				pollSpeechRegistry(L"SOFTWARE\\Microsoft\\Speech_OneCore\\Voices");
#else
				pollSpeechRegistry("SOFTWARE\\Microsoft\\Speech\\Voices");
				pollSpeechRegistry("SOFTWARE\\Microsoft\\Speech_OneCore\\Voices");
#endif
				return true;
			}

			bool pollSpeechRegistry(tts::string key)
			{
				HRESULT hr = 0;

				tts::stringstream locationss;
				locationss << "HKEY_LOCAL_MACHINE\\" << key;

				tts::string location = locationss.str();

				locationss << "\\Tokens";

				tts::stringstream keyss;
				keyss << key << "\\Tokens";

				//key = locationss.str();

				HKEY mainKey;

				hr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyss.str().c_str(), NULL, KEY_READ | KEY_ENUMERATE_SUB_KEYS, &mainKey);

				if (hr == ERROR_SUCCESS)
				{
					DWORD csize = 1024;
					TCHAR *tmpkeyname = new TCHAR[csize];

					uint32_t keyi = 0;


					std::vector<tts::string> keynameList;
					tts::string keyname;
					keyname.clear();


					DWORD tmpsize = csize;

					hr = RegEnumKeyEx(mainKey, keyi, tmpkeyname, &tmpsize, NULL, NULL, NULL, NULL);
					while (hr == ERROR_SUCCESS)
					{
						keyname = tmpkeyname;

						keynameList.push_back(keyname);

						tts::stringstream vss;
						vss << keyss.str() << "\\" << keyname;

						types::Voice vz = voiceRegParser(vss.str());
						vz.tokenlocation = location;

						types::Voice civz = caseinsensitize(vz);
						caseinsensitiveVoices.push_back(civz);

						v.push_back(vz);

						++keyi;
						tmpsize = csize;
						hr = RegEnumKeyEx(mainKey, keyi, tmpkeyname, &tmpsize, NULL, NULL, NULL, NULL);
					}

					delete[] tmpkeyname;


				}

				return false;
			}


			types::Voice voiceRegParser(tts::string key)
			{
				HRESULT hr = 0;
				types::Voice v;
				v.zero();

				uint32_t vali = 255;
				DWORD tmpvali = vali;
				TCHAR* val = new TCHAR[vali];

				HKEY mainKey;

				tts::stringstream keyss;
				keyss /*<< L"SOFTWARE\\Microsoft\\Speech\\Voices\\Tokens\\"*/ << key;

				std::wstring searchkey;

				hr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyss.str().c_str(), NULL, KEY_READ, &mainKey);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}

				searchkey = L"CLSID";

				tmpvali = vali;
				hr = RegQueryValueEx(mainKey, tts::string(searchkey.begin(), searchkey.end()).c_str(), NULL, NULL, (LPBYTE)val, &tmpvali);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}

				v.classid = val;

				keyss << "\\Attributes\\";
				//searchkey = keyss.str();

				hr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyss.str().c_str(), NULL, KEY_READ, &mainKey);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}

				searchkey = L"Age";

				tmpvali = vali;
				hr = RegQueryValueEx(mainKey, tts::string(searchkey.begin(), searchkey.end()).c_str(), NULL, NULL, (LPBYTE)val, &tmpvali);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}
#ifdef UNICODE
				if (wcscmp(L"Adult", val) == 0)
					v.attributes.age = types::VoiceAgeE::Adult;
				else if (wcscmp(L"Adult Senior", val) == 0)
					v.attributes.age = types::VoiceAgeE::Senior;
#else
				if (strcmp("Adult", val) == 0)
					v.attributes.age = types::VoiceAgeE::Adult;
				else if (strcmp("Adult Senior", val) == 0)
					v.attributes.age = types::VoiceAgeE::Senior;
#endif
				searchkey = L"Gender";
				tmpvali = vali;
				hr = RegQueryValueEx(mainKey, tts::string(searchkey.begin(), searchkey.end()).c_str(), NULL, NULL, (LPBYTE)val, &tmpvali);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}
#ifdef UNICODE
				if (wcscmp(L"Male", val) == 0)
					v.attributes.gender = types::VoiceGenderE::Male;
				else if (wcscmp(L"Female", val) == 0)
					v.attributes.gender = types::VoiceGenderE::Female;
#else
				if (strcmp("Male", val) == 0)
					v.attributes.gender = types::VoiceGenderE::Male;
				else if (strcmp("Female", val) == 0)
					v.attributes.gender = types::VoiceGenderE::Female;
#endif
				searchkey = L"Language";
				tmpvali = vali;
				hr = RegQueryValueEx(mainKey, tts::string(searchkey.begin(), searchkey.end()).c_str(), NULL, NULL, (LPBYTE)val, &tmpvali);

#if UNICODE
				std::wstring lts((wchar_t*)val);
				
				std::string lt = boost::locale::conv::from_utf(lts, "utf-8");
#else
				std::string lt(val);
#endif
				
				DWORD dwLang = (DWORD)strtol(lt.c_str(), NULL, 16);
				
				WORD vlangid = PRIMARYLANGID(dwLang);

				
				
				//WORD vsublangid = SUBLANGID(vx);

				tts::string strLang = _T("");

				for (types::LangItem li : _primaryLangLUT)
				{
					if (li.id == vlangid)
					{
						strLang = li.name;
						break;
					}
				}

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}

				v.attributes.language = lo::translate(strLang);

				v.attributes.languageCode = val;

				searchkey = L"Name";

				tmpvali = vali;
				hr = RegQueryValueEx(mainKey, tts::string(searchkey.begin(), searchkey.end()).c_str(), NULL, NULL, (LPBYTE)val, &tmpvali);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}

				v.attributes.name = val;
				searchkey = L"Vendor";

				tmpvali = vali;
				hr = RegQueryValueEx(mainKey, tts::string(searchkey.begin(), searchkey.end()).c_str(), NULL, NULL, (LPBYTE)val, &tmpvali);

				if (hr != ERROR_SUCCESS)
				{
					v.zero();
					delete[] val;
					return v;
				}

				v.attributes.vendor = val;

				delete[] val;

				return v;

			}


			types::Voice caseinsensitize(const types::Voice &v)
			{
				types::Voice vout = v;

#ifdef USING_BOOST
				boost::to_lower(vout.attributes.name);
				boost::to_lower(vout.attributes.vendor);
#endif
				return vout;
			}

			const types::Voices get(const types::VoiceAttributes *like, bool fuzzy = true)
			{
				if (like == nullptr)
				{
					return v;
				}
				else if (fuzzy == false)
				{
					types::Voices vl;

					types::Voices *vv = &v;
					types::Voices *svv = &v;
#ifdef USING_BOOST
					vv = &caseinsensitiveVoices;

					
					if (like->age != types::VoiceAgeE::UNKNOWN)
					{
						if (like->gender != types::VoiceGenderE::UNKNOWN)
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{
																								
												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language //&&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
						else//like->gender != VoiceGender_UNKNOWN
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language //&&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age //&&
												//vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
					}
					else//VoiceAge_UNKNOWN
					{
						if (like->gender != types::VoiceGenderE::UNKNOWN)
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language //&&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
						else//like->gender != VoiceGender_UNKNOWN
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												vt.attributes.language == like->language //&&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name &&
												vt.attributes.vendor == like->vendor)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												0
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
					}
					return vl;
				}
				else if (fuzzy == true)
				{
					types::Voices vl;

					types::Voices *vv = &v;
					types::Voices *svv = &v;
#ifdef USING_BOOST
					vv = &caseinsensitiveVoices;
#endif

					if (like->age != types::VoiceAgeE::UNKNOWN)
					{
						if (like->gender != types::VoiceGenderE::UNKNOWN)
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) //&&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
						else//like->gender != VoiceGender_UNKNOWN
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) //&&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (vt.attributes.age == like->age //&&
												//vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//matchString(vt.attributes.name, like->name) &&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
					}
					else//VoiceAge_UNKNOWN
					{
						if (like->gender != types::VoiceGenderE::UNKNOWN)
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) //&&
												//matchString(vt.attributes.name, like->name) &&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
						else//like->gender != VoiceGender_UNKNOWN
						{
							if (!like->language.empty())
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language) &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												matchLanguage(vt.attributes.language, like->language)												
												//matchString(vt.attributes.name, like->name) &&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
							else//like->language.empty()
							{
								if (!like->name.empty())
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												matchString(vt.attributes.name, like->name) //&&
												//matchString(vt.attributes.vendor, like->vendor)
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
								else//like->name.empty()
								{
									if (!like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender &&
												//vt.attributes.language == like->language &&
												//matchString(vt.attributes.name, like->name) &&
												matchString(vt.attributes.vendor, like->vendor))
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
									else//like->vendor.empty())
									{
										uint32_t idx = 0;
										for (types::Voice vt : *vv)
										{
											if (//vt.attributes.age == like->age &&
												//vt.attributes.gender == like->gender //&&
												//vt.attributes.language == like->language &&
												//vt.attributes.name == like->name //&&
												//vt.attributes.vendor == like->vendor
												0
												)
											{

												vl.push_back(svv->at(idx));
											}
											++idx;
										}
									}
								}
							}
						}
					}
#else
					return get(like,false);
#endif	
					return vl;
				}

				types::Voices vx;
				return vx;
			}

			bool matchString(tts::string input, tts::string test)
			{
				bool contains = false;
#ifndef USING_BOOST
				return contains;
#else
				boost::to_lower(input);
				boost::to_lower(test);


				std::vector<tts::string> strl;
				boost::split(strl, test, boost::is_any_of(_split));

				for (tts::string s : strl)
				{
					if (boost::algorithm::contains(input, s))
					{
						contains = true;
					}
					else
					{
						contains = false;
					}
				}

				return contains;
#endif
			}

			bool matchLanguage(tts::string a, tts::string b)
			{
				boost::algorithm::to_lower(a);
				boost::algorithm::to_lower(b);

				if (a == b)
				{
					return true;
				}
				return false;
			}
#

			void setFuzzySplit(tts::string split)
			{
				_split = split;
			}

		public:
			VoiceManager *_q;
			types::Voices v;
			tts::string _split;

			types::Voices caseinsensitiveVoices;

			std::vector<types::LangItem> _primaryLangLUT;
			std::vector<types::LangItem> _primaryLangLUTInsensitive;

		};
	}
}

VoiceManager::VoiceManager()
{
	_p = new VoiceManagerPrivate(this);
	refresh();
}
	
VoiceManager::~VoiceManager()
{
	delete _p;
}

bool VoiceManager::refresh()
{
	return _p->refresh();
}

const types::Voices VoiceManager::get(const types::VoiceAttributes *like, bool fuzzy)
{
#ifdef USING_BOOST
	return _p->get(like, fuzzy);
#else
	return _p->get(like, false);
#endif
}

void VoiceManager::setFuzzySplit(tts::string split)
{
	_p->setFuzzySplit(split);
}

inline std::string ttsstrtoutf8(const tts::string &in, std::wstring_convert<std::codecvt_utf8<wchar_t>> &cnv)
{
	std::wstring t(in.begin(), in.end());

	std::string out = cnv.to_bytes(t);

	return out;

}


tts::string VoiceManager::json(const types::Voices &v)
{
#ifdef USING_RAPIDJSON
	namespace rj = rapidjson;

	rj::Document d;
	d.SetObject();

	
	
	rj::Value header;
	header.SetObject();
	rj::Document::AllocatorType &alloc = d.GetAllocator();

	header.AddMember("Voice-Number", v.size(), alloc);
	header.AddMember("Writing-Application", rj::Value(TTSCMD_APPLICATION_NAME, alloc), alloc);
	header.AddMember("Application-Version", rj::Value(TTSCMD_VERSION, alloc), alloc);

	d.AddMember("header",header, alloc);

	rj::Value voicesval("Voices", alloc);
	voicesval.SetArray();

	uint32_t i = 0;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

	for (types::Voice vz : v)
	{
		rj::Value voiceval;
		voiceval.SetObject();

		voiceval.AddMember("CLSID", rj::Value(ttsstrtoutf8(vz.classid, conv).c_str(), alloc), alloc);

		types::VoiceAttributes a = vz.attributes;

		voiceval.AddMember("name", rj::Value(ttsstrtoutf8(a.name, conv).c_str(), alloc), alloc);
		voiceval.AddMember("language", rj::Value(ttsstrtoutf8(a.language, conv).c_str(), alloc), alloc);
		voiceval.AddMember("vendor", rj::Value(ttsstrtoutf8(a.vendor, conv).c_str(), alloc), alloc);
		voiceval.AddMember("age", rj::Value(ttsstrtoutf8(a.toAgeStr(), conv).c_str(), alloc), alloc);
		voiceval.AddMember("gender", rj::Value(ttsstrtoutf8(a.toGenderStr(), conv).c_str(), alloc), alloc);

		voicesval.PushBack(voiceval, alloc);		

		++i;
	}

	d.AddMember("voices", voicesval, alloc);

	rj::StringBuffer buffer;
	rj::Writer<rj::StringBuffer> writer(buffer);
	d.Accept(writer);
	const char* output = buffer.GetString();

	std::string to(output);
#if UNICODE
	tts::string o = boost::locale::conv::to_utf<wchar_t>(to, "UTF-8");
#else
	tts::string o(to.begin(),to.end());
#endif
	return o;
#else
	return tts::string();
#endif//USING_RAPIDJSON
}

tts::string VoiceManager::json(const types::VoiceAttributes *like, bool fuzzy)
{
#ifdef USING_RAPIDJSON
	types::Voices vv = get(like, fuzzy);
	return json(vv);
#else
	return tts::string();
#endif//USING_RAPIDJSON
}
