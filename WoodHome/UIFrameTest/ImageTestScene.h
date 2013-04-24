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
	virtual void OnHide();
	virtual void OnShow(void* data /* = NULL */);
	virtual void OnLoad();
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

