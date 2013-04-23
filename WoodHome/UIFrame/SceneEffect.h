#pragma once
#include "TimerManager.h"

class CScene;
class CImageBuffer;
class CGraphics;

class IEffectListner
{
public:
	virtual void OnEffect() = 0;
	virtual void OnEffectEnd(CScene* src , CScene* dest) = 0;
};

class CSceneEffect : public ITimerListener
{
public:
	CSceneEffect(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic);
	virtual ~CSceneEffect(void);
public:
	void Start(CScene* src , CScene* dest);
private:
	virtual void Effect() = 0;
	virtual void OnTimer(TimerID timerid);
protected:
	IEffectListner* mListner;
	CImageBuffer* mSrcBuffer;
	CImageBuffer* mDstBuffer;
	CScene* mSrcScene;
	CScene* mDstScene;
	CGraphics* mGraphics;
	int mInterval;
	int mCurFrames;
	int mTotaolFrames;
	int mTimerId;
};

