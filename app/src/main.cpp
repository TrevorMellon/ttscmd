/*****************************************************
*                                                    *
*  Copyright (c) 2016 Trevor Mellon                  *
*  For further information contact t@jno.io          *
*                                                    *
*  Licensed under the BSD 3-clause license           *
*  See LICENCE file for more information             *
*                                                    *
******************************************************/

#include <Application.h>

typedef std::basic_string<TCHAR> tstring;
typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstringstream;

namespace lo = boost::locale;
namespace po = boost::program_options;

using namespace io_jno;



#ifdef UNICODE
int wmain(int argc, TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	Application app(argc, argv);
	app.parseOptions();
	return 0;
}



