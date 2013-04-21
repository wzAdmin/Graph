#include "CommonFun.h"
#include <stdlib.h>
#include "Memory_Check.h"
std::wstring AnsiToWstring( const char* src , int len )
{
	if(len = -1)
		len = strlen(src);
	wchar_t* wcs = NEW_LEAKCHECK wchar_t[len + 1];
	memset(wcs,0,(len + 1)*sizeof(wchar_t));
	setlocale(LC_ALL, "chs");
	mbstowcs(wcs,src,len);
	std::wstring result(wcs);
	DELETEARR_LEAKCHECK(wcs);
	return result;
}

std::wstring AnsiToWstring( const std::string& str )
{
	return AnsiToWstring(str.c_str(),str.length());
}
