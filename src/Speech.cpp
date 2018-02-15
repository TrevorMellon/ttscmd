/*****************************************************
*                                                    *
*  copyright (c) 2018 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#include <io_jno/tts/Speech.h>
#include <io_jno/tts/Types.h>

#include <sapi.h>
#include <sphelper.h>

#include <boost/locale.hpp>

namespace lo = boost::locale;

inline std::wstring towstring(io_jno::tts::string in)
{
#if UNICODE
	return in;
#else
	std::wstring out(in.begin(), in.end());
	return out;
#endif
}

namespace io_jno
{
	namespace tts
	{
		class SpeechPrivate
		{
		public:
			SpeechPrivate()
			{
				_bVoiceSet = false;
				_bSpeakerOut = true;
			}

			~SpeechPrivate()
			{
				_cpVoice.Release();
				//CoUninitialize();
			}
		public:
			bool initVoice(types::Voice &vc)
			{
				tts::stringstream ss;

				//HRESULT hr = CoInitialize(NULL);				

				CComPtr<ISpObjectToken>       cpVoiceToken = 0;
				CComPtr<IEnumSpObjectTokens>  cpEnum = 0;


				HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpVoice), (LPVOID *)&_cpVoice);

				if (FAILED(hr))
				{
					std::cerr << lo::translate("Failed to retrieve CLSID for COM server") << std::endl;
					exit(-1);
				}

				std::wstringstream vss;

				vss << towstring(vc.tokenlocation);

				if (vc.classid.empty())
					hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
				else
				{
					std::wstringstream wss;
					wss << L"name=" << towstring(vc.attributes.name);
					hr = SpEnumTokens(vss.str().c_str(), wss.str().c_str(), NULL, &cpEnum);
				}

				hr = cpEnum->Next(1, &cpVoiceToken, NULL);

				if (SUCCEEDED(hr))
				{
					hr = _cpVoice->SetVoice(cpVoiceToken);
					ISpObjectTokenCategory* tc;
					cpVoiceToken->GetCategory(&tc);

				}

				//cpVoice.Release();
				cpEnum.Release();
				cpVoiceToken.Release();

				if (SUCCEEDED(hr))
				{
					_bVoiceSet = true;
				}
				
				_bVoiceSet = false;
				return _bVoiceSet;
				
			}

			void setVoice(types::Voice &vc)
			{
				if (checkVoice(vc))
				{
					initVoice(vc);
				}
			}

			bool checkVoice(types::Voice &vc)
			{
				if (vc.classid.empty())
				{
					return false;
				}
				return true;
			}

			bool speak(tts::string say)
			{
				if (!_bVoiceSet)
				{
					return false;
				}

				CComPtr<IEnumSpObjectTokens>   cpOutEnum;
				CComPtr<ISpObjectToken>        cpAudioOutToken;

				HRESULT hr = SpEnumTokens(SPCAT_AUDIOOUT, NULL, NULL, &cpOutEnum);

				ULONG outputCount = 0;
				cpOutEnum->GetCount(&outputCount);

				if (outputCount > 0)
				{
					cpOutEnum->Next(1, &cpAudioOutToken, NULL);

					std::wstring twstr(say.begin(), say.end());

					hr = _cpVoice->SetOutput(cpAudioOutToken, TRUE);

					if (SUCCEEDED(hr))
					{
						hr = _cpVoice->Speak(twstr.c_str(), SPF_DEFAULT, NULL);
						if (SUCCEEDED(hr))
						{
							return true;
						}
					}
					else
					{
						return false;
					}
				}
				
				return false;
			}

			bool wav(tts::string say, tts::string wavfile)
			{
				if (!_bVoiceSet)
				{
					return false;
				}
				
				std::wstring twstr(say.begin(), say.end());

				CSpStreamFormat			cAudioFmt;
				CComPtr<ISpStream>		cpStream;

				HRESULT hr = cAudioFmt.AssignFormat(SPSF_44kHz16BitMono);

				if (SUCCEEDED(hr))
				{
					std::wstring wwav = towstring(wavfile);
					hr = SPBindToFile(wwav.c_str(), SPFM_CREATE_ALWAYS,
						&cpStream, &cAudioFmt.FormatId(), cAudioFmt.WaveFormatExPtr());
				}
				if (SUCCEEDED(hr))
				{
					hr = _cpVoice->SetOutput(cpStream, TRUE);
				}

				if (SUCCEEDED(hr))
				{
					hr = _cpVoice->Speak(twstr.c_str(), SPF_DEFAULT, NULL);
				}

				if (SUCCEEDED(hr))
				{
					return true;
				}
				return false;

			}

			public:
				types::Voice _vc;
				bool _bVoiceSet;
				bool _bSpeakerOut;
				CComPtr<ISpVoice>             _cpVoice;
		};
	}
}

using namespace io_jno::tts;
using namespace io_jno;

Speech::Speech()
{
	_p = new SpeechPrivate();
}

Speech::~Speech()
{
	if (_p)
	{
		delete _p;
	}
	_p = nullptr;
}

bool Speech::speak(tts::string say)
{
	return _p->speak(say);
}

bool Speech::wav(tts::string say, tts::string wavfile)
{
	return _p->wav(say, wavfile);
}

void Speech::setVoice(types::Voice &vc)
{
	_p->setVoice(vc);
}