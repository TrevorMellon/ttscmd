#include <Application.h>
#include <io_jno/tts/VoiceManager.h>
#include <io_jno/tts/Unicode.h>
#include <io_jno/tts/Version.h>
#include <io_jno/tts/Speech.h>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>

#include <string>
#include <sstream>

#include <sapi.h>
#include <sphelper.h>

#include <atlbase.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace lo = boost::locale;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

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

#if UNICODE
Application::Application(int argc, TCHAR** argv)
{
	_argc = argc;
	_argv = argv;

	_allopts = nullptr;

	lo::generator gen;
	_sysloc = gen("");
	std::string locname;
	try
	{
		locname = std::use_facet<boost::locale::info>(_sysloc).name();
	}
	catch (std::bad_cast &e)
	{
		std::cerr << "Could not get profile: " << e.what() << std::endl;
	}
	_sysloc = gen(locname);

	std::locale::global(_sysloc);
	std::wcout.imbue(_sysloc);
	std::cout.imbue(_sysloc);

	TCHAR *tempfilename = new TCHAR[MAX_PATH];
	GetModuleFileName(NULL, tempfilename, MAX_PATH);
	fs::path exepath(tempfilename);
	delete[] tempfilename;
	fs::path root = exepath.parent_path();
	root = root.parent_path();
	boost::filesystem::path p(root);
	p += "\\share\\locale";

	gen.add_messages_path(p.string());
	gen.add_messages_domain("ttscmd");

	parseOptions();
}
#else
Application::Application(int argc, char** argv)
{
	_argc = argc;
	_argv = argv;

	_allopts = nullptr;

	lo::generator gen;
	_sysloc = gen("");

	std::string locname = std::use_facet<boost::locale::info>(_sysloc).name();
	_sysloc = gen(locname);

	std::locale::global(_sysloc);
	std::wcout.imbue(_sysloc);
	std::cout.imbue(_sysloc);

	TCHAR *tempfilename = new TCHAR[MAX_PATH];
	GetModuleFileName(NULL, tempfilename, MAX_PATH);
	fs::path exepath(tempfilename);
	delete[] tempfilename;
	fs::path root = exepath.parent_path();
	root = root.parent_path();
	boost::filesystem::path p(root);
	p += "\\share\\locale";

	gen.add_messages_path(p.string());
	gen.add_messages_domain("ttscmd");

	parseOptions();
}
#endif

Application::~Application()
{
	if (_allopts)
		delete _allopts;
}

void Application::parseOptions()
{
	try
	{
		tts::types::Voice vz;
		tts::VoiceManager v;
		vz = voiceOption();

		sayOption();

		if (vz.attributes.name.empty())
		{


			if (listOption()
				|| helpOption()
				|| versionOption())
			{
				exit(0);
			}
			else
			{
				auto vv = v.get();
				if (vv.empty())
				{
					std::cerr << "No voices installed on this system";
					exit(1);
				}
				vz = vv.at(0);
				speak(vz);
			}
		}
		else
		{
			speak(vz);
		}
	}
	catch (boost::bad_lexical_cast &e)
	{
		std::cerr << "Bad input value: " << e.what() << std::endl;
		exit(-1);
	}
}

void Application::Options()
{
	std::string locstr;

#if UNICODE
	_strsay = lo::translate(L"What would you like me to say?");
#endif

	po::options_description genopts(lo::translate("Primary Options"));
	genopts.add_options()
		("version,v", lo::translate("Display version information").str().c_str())
		("help,h", lo::translate("Show help information").str().c_str())
#if UNICODE
		("say,s", po::wvalue<std::wstring>(&_strsay), lo::translate("Speak the following text").str().c_str())
#else
		("say,s", po::value<tts::string>(&_strsay)->default_value(lo::translate("What would you like me to say?").str().c_str()), lo::translate("Speak the following text").str().c_str())
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
		("age,a", po::value<std::string>(&sa), lo::translate("Based on age").str().c_str())
		("gend,g", po::value<std::string>(&sg), lo::translate("Based on gender").str().c_str())
		("lang,n", po::value<std::string>(&sl), lo::translate("Based on language code").str().c_str())
		("name,m", po::value<std::string>(&sn), lo::translate("Based on voice name").str().c_str())
		("vend,e", po::value<std::string>(&sv), lo::translate("Based on voice vendor").str().c_str())
		;

	po::options_description inoutopts(lo::translate("Input/Output Options").str().c_str());
	inoutopts.add_options()
		//("file", po::value<std::string>(), "Read from text file")
		("wav", po::value<std::string>(), lo::translate("Write to wav file instead of speakers").str().c_str())
		;

	if (_allopts)
		delete _allopts;

	po::options_description *allopts = new po::options_description();
	allopts->add(genopts);
	allopts->add(listopts);
	allopts->add(searchopts);
	allopts->add(inoutopts);
	
	_allopts = allopts;

	try
	{
#if UNICODE
		po::store(po::parse_command_line(_argc, (wchar_t**)_argv, *allopts), _vm);
#else
		po::store(po::parse_command_line(_argc, _argv, *allopts), _vm);
#endif
	}
	catch (std::exception &e)
	{
		std::cerr << e.what();
		exit(1);
	}
}

void Application::localeOption()
{
	if (_vm.count(lo::translate("locale")))
	{
		std::string locstr = _vm["locale"].as<std::string>();

#if _DEBUG
		std::cout << "found locale: " << locstr << std::endl;
#endif
		lo::generator gen;
		std::stringstream locss;
		locss << locstr << ".UTF-8";

		std::locale loc = gen(locss.str());

		std::locale::global(loc);
		std::wcout.imbue(loc);
		std::cout.imbue(loc);
		_sysloc = loc;
	}
}

tts::types::Voice Application::voiceOption()
{
	tts::VoiceManager v;
	tts::types::Voice vz;
	vz.zero();

	if (_vm.count("age") ||
		_vm.count("gend") ||
		_vm.count("lang") ||
		_vm.count("name") ||
		_vm.count("vend"))
	{
		tts::types::VoiceAttributes vatt;
		vatt.zero();
		if (_vm.count("age"))
		{
			tts::string tmpstr;
			try
			{
				tmpstr = _vm["age"].as<tts::string>();
			}
			catch (boost::bad_any_cast &e)
			{
				std::cerr << "age [bad cast]: " << e.what() << std::endl;
				exit(-1);
			}
			boost::to_lower(tmpstr);
			vatt.fromAgeStr(tts::string(tmpstr.begin(), tmpstr.end()));
		}
		if (_vm.count("gend"))
		{
			tts::string tmpstr;
			try
			{
				tmpstr = _vm["gend"].as<tts::string>();
			}
			catch (boost::bad_any_cast &e)
			{
				std::cerr << "gend [bad cast]: " << e.what() << std::endl;
				exit(-1);
			}
			boost::to_lower(tmpstr);
			vatt.fromGenderStr(tts::string(tmpstr.begin(), tmpstr.end()));
		}
		if (_vm.count("lang"))
		{
			tts::string tmpstr;
			try
			{
				tmpstr = _vm["lang"].as<tts::string>();
			}
			catch (boost::bad_any_cast &e)
			{
				std::cerr << "lang [bad cast]: " << e.what() << std::endl;
				exit(-1);
			}
			boost::to_lower(tmpstr);
			vatt.language = tts::string(tmpstr.begin(), tmpstr.end());
		}
		if (_vm.count("name"))
		{
			tts::string tmpstr;
			try
			{
				tmpstr = _vm["name"].as<tts::string>();
			}
			catch (boost::bad_any_cast &e)
			{
				std::cerr << "name [bad cast]: " << e.what() << std::endl;
				exit(-1);
			}
			boost::to_lower(tmpstr);
			vatt.name = tts::string(tmpstr.begin(), tmpstr.end());
		}
		if (_vm.count("vend"))
		{
			std::string tmpstr;
			try
			{
				tmpstr = _vm["vend"].as<std::string>();
			}
			catch (boost::bad_any_cast &e)
			{
				std::cerr << "vend [bad cast]: " << e.what() << std::endl;
				exit(-1);
			}
			boost::to_lower(tmpstr);
			vatt.vendor = tts::string(tmpstr.begin(), tmpstr.end());
		}

		tts::types::Voices vcs = v.get(&vatt, true);

		if (vcs.size() > 0)
			vz = vcs.at(0);

		if (_vm.count("list"))
		{
			if (_vm.count("json"))
			{
				tts::string t = v.json(vcs);
				std::wcout << towstring(t) << std::endl;
			}
			else if (_vm.count("jsonfile"))
			{
				tts::string t = v.json(vcs);
				tts::string ofilea;

				try
				{
					ofilea = _vm["jsonfile"].as<tts::string>();
				}
				catch (boost::bad_any_cast &e)
				{
					std::cerr << "Could not determine output filename: " << e.what();
					exit(-1);
				}
				
				std::wstring ofile = towstring(ofilea);
				std::wofstream ofs(ofile);

				ofs << towstring(t);
				ofs.close();
			}
			else{

				for (tts::types::Voice vvz : vcs)
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
			exit(0);
		}
		
	}
	
	return vz;
}

bool Application::listOption()
{
	tts::VoiceManager v;
	
	if (_vm.count("list"))
	{
		tts::types::Voices vv = v.get();

		if (_vm.count("json"))
		{
			tts::string t = v.json(vv);
#if UNICODE
			std::cout << boost::locale::conv::from_utf(t, _sysloc) << std::endl;
#else
			std::cout << t << std::endl;
#endif
		}
		else if (_vm.count("jsonfile"))
		{
			tts::string t = v.json(vv);
			std::string ofilea = _vm["jsonfile"].as<std::string>();

			std::wstring ofile = boost::locale::conv::to_utf<wchar_t>(ofilea, "UTF-8");
			std::wofstream ofs(ofile);

			ofs << towstring(t);
			ofs.close();
		}
		else
		{

			for (tts::types::Voice vvz : vv)
			{
				tts::string gend = vvz.attributes.toGenderStr();
#if UNICODE
				std::cout << std::endl;
				std::cout << lo::translate("Voice\t\t: ") << boost::locale::conv::from_utf(vvz.attributes.name, _sysloc) << std::endl;
				std::cout << lo::translate("Gender\t\t: ") << boost::locale::conv::from_utf(gend, _sysloc) << std::endl;
				std::cout << lo::translate("Age\t\t: ") << boost::locale::conv::from_utf(vvz.attributes.toAgeStr(), _sysloc) << std::endl;
				std::cout << lo::translate("Vendor\t\t: ") << boost::locale::conv::from_utf(vvz.attributes.vendor, _sysloc) << std::endl;
				std::cout << lo::translate("Language\t: ") << boost::locale::conv::from_utf(vvz.attributes.language, _sysloc) << std::endl;
				std::cout << lo::translate("LangCode\t: ") << boost::locale::conv::from_utf(vvz.attributes.languageCode, _sysloc) << std::endl;
#else
				std::cout << std::endl;
				std::cout << lo::translate("Voice\t\t: ") << vvz.attributes.name << std::endl;
				std::cout << lo::translate("Gender\t\t: ") << gend << std::endl;
				std::cout << lo::translate("Age\t\t: ") << vvz.attributes.toAgeStr() << std::endl;
				std::cout << lo::translate("Vendor\t\t: ") << vvz.attributes.vendor << std::endl;
				std::cout << lo::translate("Language\t: ") << vvz.attributes.language << std::endl;
				std::cout << lo::translate("LangCode\t: ") << vvz.attributes.languageCode << std::endl;
#endif
				std::cout << std::endl;
			}
		}
		exit(0);
	}
	return false;
}

bool Application::sayOption()
{
	if (_vm.count("say"))
	{
#if UNICODE
		std::wstringstream ss_say;
		ss_say.imbue(_sysloc);
		ss_say << _vm["say"].as<tts::string>();
		_strsay = ss_say.str();
#else
		_strsay = _vm["say"].as<tts::string>();
#endif
		return true;
	}

	return false;
}

bool Application::helpOption()
{
	if (_vm.count("help"))
	{
		std::cout << *_allopts << std::endl;
		exit(0);
	}
	return false;
}

bool Application::versionOption()
{
	if (_vm.count("version"))
	{
		try
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
			std::cout << "Locale:" << std::use_facet<boost::locale::info>(_sysloc).name() << std::endl;
			std::cout << std::endl;
		}
		catch (std::bad_cast &e)
		{
			std::cerr << "FATAL ERROR: " << e.what() << std::endl;
			exit(-1);
		}

		exit(0);
	}
	return false;
}

void Application::speak(io_jno::tts::types::Voice &vz)
{
	HRESULT hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		std::cerr << lo::translate("Failed to start COM server") << std::endl;
		exit(-1);
	}

	tts::Speech *sp = new tts::Speech();

	sp->setVoice(vz);
	sp->speak(_strsay);

	delete sp;

	CoUninitialize();	
}