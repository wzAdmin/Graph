#pragma once
#include <stdarg.h>
#include <stdio.h>
#ifdef _MSC_VER
inline bool OutTrace(const char* format,...)
{
	va_list arg;
	va_start(arg,format);
	vprintf(format,arg);
	va_end(arg);
	return true;
}
#endif
#ifdef _DEBUG
#define DebugTrace OutTrace
#else
#define DebugTrace
#endif