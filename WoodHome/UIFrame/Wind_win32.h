#pragma once
#include "uiwindow.h"
#include <Windows.h>
#define MAX_INPUT_WORDS 256
class CWind_win32 :
	public CUIWindow
{
public:
	CWind_win32(Style_Window id);
	~CWind_win32(void);
private:
	virtual void MessageTo(WindID windowId,const SystemMessage& msg );
	virtual void ShowWindow();
	virtual void HideWindow();
	virtual void Minimize();
	virtual void SetPostion(int x , int y);
	virtual void DrawToWindow(const CBound* drawBound = NULL);
	virtual void BufferToWindow(const CImageBuffer* buffer);
	virtual void Start();
	virtual WindID GetID(){return int(mhWnd);}
	virtual void Quit();
	void DrawWin32(HDC hdc , const CBound* drawBound = NULL);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND mhWnd;
	wchar_t mInputChar[MAX_INPUT_WORDS];
	int mInputCount;
};

