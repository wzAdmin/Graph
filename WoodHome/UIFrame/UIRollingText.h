#pragma once
#include "uitextview.h"
#include "TimerManager.h"

class UI_API CUIRollingText :
	public CUITextView , public ITimerListener
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUIRollingText;}
	CUIRollingText(void);
	~CUIRollingText(void);
public:
	void Text(const std::wstring& wcs);
private:
	virtual void Load(const slim::XmlNode* node);
	virtual void Draw(CGraphics* pGraphic);
	virtual void OnTimer(TimerID timerid);
	void Init( CGraphics* pGraphic);
private:
	TimerID mTimerid;
	int mRollFrequency;
	int mIndex;
	int mOffset;
	int mCurCharWidth;
	bool mRolling;
	bool mInited;
};
