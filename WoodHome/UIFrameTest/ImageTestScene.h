#pragma once
#include "scene.h"
#include "TimerManager.h"
class CImageTestScene :
	public CScene , public ITimerListener
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CImageTestScene;}
	CImageTestScene(void);
	~CImageTestScene(void);
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual void Load(const slim::XmlNode* node);
	void OnBtnbackClick();
	void OnBtnScaleXClick();
	void OnBtnScaleYClick();
	void OnBtnRotateClick();
	void OnBtnSkewXClick();
	void OnBtnSkewYClick();
	void OnTimer(TimerID timerid);
private:
	float mRotate;
	float mScaleX;
	float mScaleY;
	float mSkewX;
	float mSkewY;
	TimerID mtimeid;
};

