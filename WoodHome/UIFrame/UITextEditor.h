#pragma once
#include "uitextview.h"
class UI_API CUITextEditor :
	public CUITextView
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUITextEditor;}
	CUITextEditor(void);
	~CUITextEditor(void);
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual bool OnInputChar(const wchar_t* wcs,int len);
	virtual bool OnLBtnDown(int x ,int y);
	virtual bool OnLBtnUp(int x ,int y);
	virtual bool OnMouseMove(int x ,int y);
	virtual void OnFocusOut(CUIObject* newFocus);
	virtual void OnTimer(TimerID timerid);
private:
	TimerID mCurosTimer;
	bool mIsCurosShowing;
};

