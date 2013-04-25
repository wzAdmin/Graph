#pragma once
#ifdef _DLL
#define UI_API _declspec(dllexport)
#else
#define UI_API
#endif
#ifndef NULL
#define NULL 0
#endif
enum MessageID{
	LBtnDown,
	LBtnUp,
	RBtnDown,
	RBtnUp,
	MouseMove,
	KeyDown,
	KeyUp,
	CharInput,
};
typedef struct _SystemMessage
{
	MessageID msg;
	int wParam;
	int lParam;
}SystemMessage;