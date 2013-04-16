#pragma once
#include "uiwindow.h"
#include <Windows.h>
class CWind_win32 :
	public CUIWindow
{
public:
	CWind_win32(Style_Window id);
	~CWind_win32(void);
	int GetWindID(){return int(mhWnd);}
private:
	virtual void MessageTo(WindID windowId,const SystemMessage& msg );
	virtual void ShowWindow();
	virtual void HideWindow();
	virtual void Minimize();
	virtual void SetPostion(int x , int y);
	virtual void DrawToWindow();
	virtual void Run();

	void DrawWin32(HDC hdc);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND mhWnd;
};

