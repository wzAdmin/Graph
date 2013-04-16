#pragma once
#ifdef _DLL
#define UI_API _declspec(dllexport)
#else
#define UI_API
#endif

enum MessageID{
	MouseDown,
	MouseUp,
	MouseMove,
	KeyDown,
	KeyUp,
	Char,
};
typedef struct _SystemMessage
{
	MessageID msg;
	int wParam;
	int lParam;
}SystemMessage;