#ifndef APPLICATION_H
#define APPLICATION_H

#include <locale>
#include <io_jno/tts/Voices.h>
#include <io_jno/tts/Unicode.h>

#include <boost/program_options.hpp>

class Application
{
public:
#if UNICODE
	Application(int argc, TCHAR** argv);
#else
	Application(int argc, char** argv);
#endif
	~Application();
public:
	void speak(io_jno::tts::VoiceZ &vz);
public:
	void parseOptions();
private:
	void Options();

	void localeOption();
	io_jno::tts::VoiceZ voiceOption();
	bool listOption();
	bool sayOption();
	bool helpOption();
	bool versionOption();
private:
	int _argc;
#if UNICODE
	TCHAR **_argv;
#else
	char **_argv;
#endif
	std::locale _sysloc;
	std::string _localepath;

	boost::program_options::options_description *_allopts;
	boost::program_options::variables_map _vm;

	io_jno::tts::string _strsay;
};

#endif//APPLICATION_H