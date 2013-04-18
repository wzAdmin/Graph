#include "CommonFun.h"
#include <stdlib.h>
std::wstring AnsiToWstring( const char* src , int len )
{
	if(len = -1)
		len = strlen(src);
	wchar_t* wcs = new wchar_t[len];
	memset(wcs,0,len*sizeof(wchar_t));
	setlocale(LC_ALL, "chs");
	mbstowcs(wcs,src,len);
	std::wstring result(wcs);
	delete[] wcs;
	return result;
}

std::wstring AnsiToWstring( const std::string& str )
{
	return AnsiToWstring(str.c_str(),str.length());
}
