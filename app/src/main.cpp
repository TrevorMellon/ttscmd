/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#ifdef USING_BOOST

#include <io.jno/tts/Voices.h>
#include <io.jno/tts/Unicode.h>

#include <sapi.h>
#include <sphelper.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <locale.h>

#include <vector>


#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#if UNICODE
# include <boost/filesystem.hpp>
#endif

#include <atlbase.h>

#include <io.jno/tts/Unicode.h>
#include <io.jno/tts/Version.h>

typedef std::basic_string<TCHAR> tstring;
typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstringstream;

namespace lo = boost::locale;
namespace po = boost::program_options;

using namespace io_jno;

inline std::wstring towstring(tts::string in)
{
#if UNICODE
	return in;
#else
	std::wstring out(in.begin(), in.end());
	return out;
#endif
}

#ifdef UNICODE
int wmain(int argc, TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	lo::generator gen;
	std::locale sysloc = std::locale("");

	std::string locname = sysloc.name();
#if UNICODE
	boost::filesystem::path p("../share/locale/");

	//std::cout << "Using Translation path:" << std::endl;
	//std::cout << p << std::endl;

	gen.add_messages_path(p.string());
	gen.add_messages_domain("ttscmd");

	//std::locale fr = gen("fr_FR.UTF-8");
	std::locale fr = sysloc;
	std::locale::global(fr);
	std::wcout.imbue(fr);
	std::cout.imbue(fr);
#endif
	std::string locstr;

	tts::VoicesK v;

	tts::VoiceZ vz;
	vz.zero();

	tts::string strsay;

#if UNICODE
	strsay = lo::translate(L"What would you like me to say?");
#endif

	po::options_description genopts(lo::translate("Primary Options"));
	genopts.add_options()
		("version,v", lo::translate("Display version information").str().c_str())
		("help,h", lo::translate("Show help information").str().c_str())
#if UNICODE
		("say,s", po::wvalue<std::wstring>(&strsay), lo::translate("Speak the following text").str().c_str())
#else
		("say,s", po::value<tts::string>(&strsay)->default_value(lo::translate("What would you like me to say?").str().c_str()), lo::translate("Speak the following text").str().c_str())
#endif
		;

	std::string jsonfile;

	po::options_description listopts(lo::translate("List Options").str().c_str());
	listopts.add_options()
		("list,l", lo::translate("List voices installed on the system").str().c_str())
		("json,j", lo::translate("Use json output").str().c_str())
		("jsonfile,f", po::value<std::string>(&jsonfile), lo::translate("Write json to file").str().c_str())
		("locale", po::value<std::string>(&locstr), lo::translate("Use the included locale instead of system").str().c_str())
		;

	std::string sa, sg, sl, sn, sv;

	po::options_description searchopts(lo::translate("Search Options").str().c_str());
	searchopts.add_options()
		("age", po::value<std::string>(&sa), lo::translate("Based on age").str().c_str())
		("gend", po::value<std::string>(&sg), lo::translate("Based on gender").str().c_str())
		("lang", po::value<std::string>(&sl), lo::translate("Based on language code").str().c_str())
		("name", po::value<std::string>(&sn), lo::translate("Based on voice name").str().c_str())
		("vend", po::value<std::string>(&sv), lo::translate("Based on voice vendor").str().c_str())
		;
		//("searchageindex,sai", po::value<uint32_t>(), "Search based on age index (integer)")
		//("searchgenderindex,sgi", po::value<uint32_t>(), "Search based on gender index (integer)")
		//("searchlanguageindex,sli", po::value<uint32_t>(), "Search based on search language index (integer)")
		//("searchnameindex,sni", po::value<uint32_t>(), "Search based on voice name index")
		//("searchvendorindex,svi", po::value<uint32_t>(), "Search based on vendor index")
		

	po::options_description inoutopts(lo::translate("Input/Output Options").str().c_str());
	inoutopts.add_options()
		//("file", po::value<std::string>(), "Read from text file")
		("wav", po::value<std::string>(), lo::translate("Write to wav file instead of speakers").str().c_str())
		;

	po::options_description allopts;
	allopts.add(genopts).add(listopts).add(searchopts).add(inoutopts);

	po::variables_map vm;

	try
	{
		po::store(po::parse_command_line(argc, argv, allopts), vm);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what();
		exit(1);
	}
	
	if (vm.count(lo::translate("locale")))
	{
		locstr = vm["locale"].as<std::string>();

#if _DEBUG
		std::cout << "found locale: " << locstr << std::endl;
#endif

		std::stringstream locss;
		locss << locstr << ".UTF-8";

		std::locale loc = gen(locss.str());

		std::locale::global(loc);
		std::wcout.imbue(loc);
		std::cout.imbue(loc);
	}

	if (vm.count("age") ||
		vm.count("gend") ||
		vm.count("lang") ||
		vm.count("name") ||
		vm.count("vend"))
	{
		tts::VoiceAttributesZ vatt;
		vatt.zero();
		if (vm.count("age"))
		{
			std::string tmpstr = vm["age"].as<std::string>();	
			boost::to_lower(tmpstr);
			vatt.fromAgeStr(tts::string(tmpstr.begin(), tmpstr.end()));
		}
		if (vm.count("gend"))
		{
			std::string tmpstr = vm["gend"].as<std::string>();
			boost::to_lower(tmpstr);
			vatt.fromGenderStr(tts::string(tmpstr.begin(), tmpstr.end()));
		}
		if (vm.count("lang"))
		{
			std::string tmpstr = vm["lang"].as<std::string>();
			boost::to_lower(tmpstr);
			vatt.language = tts::string(tmpstr.begin(), tmpstr.end());
		}
		if (vm.count("name"))
		{
			std::string tmpstr = vm["name"].as<std::string>();
			boost::to_lower(tmpstr);
			vatt.name = tts::string(tmpstr.begin(), tmpstr.end());
		}
		if (vm.count("vend"))
		{
			std::string tmpstr = vm["vend"].as<std::string>();
			boost::to_lower(tmpstr);
			vatt.vendor = tts::string(tmpstr.begin(), tmpstr.end());
		}

		tts::Voices vcs = v.get(&vatt, true);

		if (vcs.size() > 0)
			vz = vcs.at(0);

		if (vm.count("list"))
		{
			if (vm.count("json"))
			{
				tts::string t = v.json(vcs);
				std::wcout << towstring(t) << std::endl;
			}
			else if (vm.count("jsonfile"))
			{
				tts::string t = v.json(vcs);
				std::string ofilea = vm["jsonfile"].as<std::string>();

				std::wstring ofile = boost::locale::conv::to_utf<wchar_t>(ofilea, "UTF-8");
				std::wofstream ofs(ofile);

				ofs << towstring(t);
				ofs.close();
			}
			else{

				for (tts::VoiceZ vvz : vcs)
				{
					std::wcout << std::endl;
					std::wcout << lo::translate(L"Voice\t\t: ") << towstring(vvz.attributes.name) << std::endl;
					std::wcout << lo::translate(L"Gender\t\t: ") << towstring(vvz.attributes.toGenderStr()) << std::endl;
					std::wcout << lo::translate(L"Age\t\t: ") << towstring(vvz.attributes.toAgeStr()) << std::endl;
					std::wcout << lo::translate(L"Vendor\t\t: ") << towstring(vvz.attributes.vendor) << std::endl;
					std::wcout << lo::translate(L"Language\t: ") << towstring(vvz.attributes.language) << std::endl;
					std::wcout << lo::translate(L"LangCode\t: ") << towstring(vvz.attributes.languageCode) << std::endl;
					std::wcout << std::endl;
				}
			}
			return 0;
		}

	}
	else if(vm.count("list"))
	{

		tts::Voices vv = v.get();

		if (vm.count("json"))
		{
			tts::string t = v.json(vv);
			std::wcout << towstring(t) << std::endl;
		}
		else if (vm.count("jsonfile"))
		{
			tts::string t = v.json(vv);
			std::string ofilea = vm["jsonfile"].as<std::string>();			
			
			std::wstring ofile = boost::locale::conv::to_utf<wchar_t>(ofilea, "UTF-8");
			std::wofstream ofs(ofile);

			ofs << towstring(t);
			ofs.close();
		}
		else{

			for (tts::VoiceZ vvz : vv)
			{
				tts::string gend = vvz.attributes.toGenderStr();
				
				std::wcout << std::endl;
				std::wcout << lo::translate(L"Voice\t\t: ") << towstring(vvz.attributes.name) << std::endl;
				std::wcout << lo::translate(L"Gender\t\t: ") << towstring(gend) << std::endl;
				std::wcout << lo::translate(L"Age\t\t: ") << towstring(vvz.attributes.toAgeStr()) << std::endl;
				std::wcout << lo::translate(L"Vendor\t\t: ") << towstring(vvz.attributes.vendor) << std::endl;
				std::wcout << lo::translate(L"Language\t: ") << towstring(vvz.attributes.language) << std::endl;
				std::wcout << lo::translate(L"LangCode\t: ") << towstring(vvz.attributes.languageCode) << std::endl;
				std::wcout << std::endl;
			}
		}
		return 0;
	}
	else if (vm.count("help"))
	{
		std::cout << allopts << std::endl;
		return 0;
	}
	else if (vm.count("version"))
	{
		std::cout << lo::translate(TTSCMD_APPLICATION_NAME) << std::endl << std::endl;
		std::cout << lo::translate("From Git rev: ") << TTSCMD_GIT_COMMIT_HASH << lo::translate(" on ") << TTSCMD_GIT_BRANCH << lo::translate(" branch.") << std::endl;
		std::cout << lo::translate("Version : ") << TTSCMD_VERSION;
#ifdef UNICODE
		std::cout << " (Unicode)";
#else
		std::cout << " (Ansi)";
#endif
		std::cout << std::endl;
		std::cout << "Locale:" << sysloc.name() << std::endl;
		std::cout << std::endl;

		return 0;
	}

	

	if (vm.count("say"))
	{
		strsay = vm["say"].as<tts::string>();
	}

	tts::stringstream ss;	
	
	HRESULT hr = CoInitialize(NULL); 
	
	

	CComPtr<ISpObjectToken>       cpVoiceToken = 0;
	CComPtr<IEnumSpObjectTokens>  cpEnum = 0;
	CComPtr<ISpVoice>             cpVoice;
	

	if (FAILED(hr))
	{
		printf(lo::translate("Failed to retrieve CLSID for COM server").str().c_str());
		return -1;
	}
		
	if (FAILED(hr))
	{
		printf(lo::translate("Failed to start COM server").str().c_str());
		return -1;
	}

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpVoice), (LPVOID *)&cpVoice);
		
		std::wstringstream vss;

		//std::wstring hklmw(L"HKEY_LOCAL_MACHINE\\");
		//tts::string hklm(hklmw.begin(), hklmw.end());

		vss << towstring(vz.tokenlocation);

		if (vz.classid.empty())
			hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
		else
		{
			std::wstringstream wss;
			wss << L"name=" << towstring(vz.attributes.name);
			hr = SpEnumTokens(vss.str().c_str(), wss.str().c_str(), NULL, &cpEnum);
		}

		

		hr = cpEnum->Next(1, &cpVoiceToken, NULL);

		if (SUCCEEDED(hr))
		{
			hr = cpVoice->SetVoice(cpVoiceToken);
			ISpObjectTokenCategory* tc;
			cpVoiceToken->GetCategory(&tc);

		}

		if (SUCCEEDED(hr))
		{
			std::wstring twstr(strsay.begin(), strsay.end());

			if (vm.count("wav"))
			{
				CSpStreamFormat			cAudioFmt;	
				CComPtr<ISpStream>		cpStream;

				hr = cAudioFmt.AssignFormat(SPSF_44kHz16BitMono);
				
				if (SUCCEEDED(hr))
				{
					std::string str = vm["wav"].as<std::string>();
					std::wstring wstr(str.begin(), str.end());
					hr = SPBindToFile(wstr.c_str(), SPFM_CREATE_ALWAYS,
						&cpStream, &cAudioFmt.FormatId(), cAudioFmt.WaveFormatExPtr());
				}
				if (SUCCEEDED(hr))
				{
					hr = cpVoice->SetOutput(cpStream, TRUE);
				}

				hr = cpVoice->Speak(twstr.c_str(), SPF_DEFAULT, NULL);

				if (SUCCEEDED(hr))
				{
					hr = cpStream->Close();
				}
			}
			else
			{
				hr = cpVoice->Speak(twstr.c_str(), SPF_DEFAULT, NULL);
			}
			
		}
		cpVoice.Release();
		cpEnum.Release();
		cpVoiceToken.Release();
	}

	CoUninitialize();
	
	return 0;
}

#endif// USING_BOOST

