#pragma once
#ifdef _DLL
#define UI_API _declspec(dllexport)
#else
#define UI_API
#endif
#ifndef NULL
#define NULL 0
#endif
#include "Memory_Check.h"
enum MessageID{
	LBtnDown,
	LBtnUp,
	RBtnDown,
	RBtnUp,
	MouseMove,
	Key,
	CharInput
};
typedef struct _SystemMessage
{
	MessageID msg;
	int wParam;
	int lParam;
}SystemMessage;