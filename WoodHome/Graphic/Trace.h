#pragma once
#include <stdarg.h>
#include <stdio.h>
#define TRACE_OUT
enum Type_Trace
{
	//white
	Trace_Normal = 0xf,

	//red
	Trace_Error = 0x4,

	//yellow
	Trace_Warning = 0x6,

	//green
	Trace_Info = 0x2
};
#ifdef _MSC_VER
#include <Windows.h>
#if defined(TRACE_OUT)

inline bool OutTrace(Type_Trace type,const char* format,...)
{
	//set color of console output
	HANDLE hconsole;
	hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole,type);

	va_list arg;
	va_start(arg,format);
	vprintf(format,arg);
	va_end(arg);
	return false;
}
#define DebugTrace OutTrace
#else
#define DebugTrace
#endif
#else
#error ("not implement yet")
#endif