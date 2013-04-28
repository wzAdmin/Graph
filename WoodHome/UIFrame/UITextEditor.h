#pragma once
#include "uitextview.h"
class UI_API CUITextEditor :
	public CUITextView
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUITextEditor;}
	CUITextEditor(void);
	~CUITextEditor(void);
public:
	unsigned int MaxInputCount()const {return mMaxInputCount;}
	void MaxInputCount( unsigned int count){mMaxInputCount = count;}
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual bool OnInputChar(const wchar_t* wcs,int len);
	virtual bool OnLBtnDown(int x ,int y);
	virtual bool OnLBtnUp(int x ,int y);
	virtual bool OnMouseMove(int x ,int y);
	virtual void OnFocusOut(CUIObject* newFocus);
	virtual void OnTimer(TimerID timerid);
	void LoseFucos();
	void DrawCuros(CGraphics* pGraphic);
	void SetIMEPos();
	void SetCurosPosition(CGraphics* pGraphic);
	bool DealSpecialChar(wchar_t ch);
	void Backspace();
private:
	static const unsigned int sDefaultCount = 256;
	unsigned int mMaxInputCount;
	TimerID mCurosTimer;
	int mCurosIndex;
	CPosition mCurosPosition;
	bool mIsCurosShowing;
};

