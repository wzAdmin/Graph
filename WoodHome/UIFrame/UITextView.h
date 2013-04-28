#pragma once
#include "UIObject.h"
#include "TimerManager.h"
#include <vector>

class UI_API CUITextView : 
	public CUIObject , public ITimerListener
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUITextView;}
	CUITextView(void);
	~CUITextView(void);
public:
	void Text(const std::wstring& wcs);
protected:
	virtual void Load(const slim::XmlNode* node);
	virtual void Draw(CGraphics* pGraphic);
private:
	virtual void OnTimer(TimerID timerid);
	void Init( CGraphics* pGraphic);
	void Wrap(CGraphics* pGraphic ,int index = 0);
	void WrapDraw(CGraphics* pGraphic);
	void WrapRoll();
	void SingleLineDraw(CGraphics* pGraphic);
	void SingleLineRoll();
protected:
	std::wstring mText;
	int mFontID;
	ALIGN malign;
private:
	TimerID mTimerid;
	int mRollFrequency;
	int mIndex;
	int mOffset;
	int mCurCharSize;
	std::vector<int> mWrapIndex;
	float mRowSpace;
	bool mIsWrap;
	bool mAutoRolling;
	bool mInited;
};
