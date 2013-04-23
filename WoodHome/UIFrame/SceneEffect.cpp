#include "SceneEffect.h"
#include "UIFrame.h"
#include "Graphics.h"
#include "ImageBuffer.h"
#include "Scene.h"

CSceneEffect::CSceneEffect(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic) : 
mListner(listner),
mCurFrames(0),
mTotaolFrames(Frames),
mGraphics(pGraphic),
mTimerId(0),
mSrcBuffer(NULL),
mDstBuffer(NULL)
{
}


CSceneEffect::~CSceneEffect(void)
{
	if(mTimerId)
		sUIFrame.GetTimerMgr()->RemoveTimer(mTimerId);
	mTimerId = 0;
	if(mSrcBuffer)
		DELETE_LEAKCHECK(mSrcBuffer);
	mSrcBuffer = NULL;
	if(mDstBuffer)
		DELETE_LEAKCHECK(mDstBuffer);
	mDstBuffer = NULL;
}

void CSceneEffect::OnTimer( TimerID timerid )
{
	mCurFrames++;
	Effect();
	mListner->OnEffect();
	if(mCurFrames >= mTotaolFrames)
	{
		mCurFrames = 0;
		sUIFrame.GetTimerMgr()->RemoveTimer(mTimerId);

		mTimerId = 0;
		DELETE_LEAKCHECK(mSrcBuffer);
		mSrcBuffer = NULL;
		DELETE_LEAKCHECK(mDstBuffer);
		mDstBuffer = NULL;
		mListner->OnEffectEnd(mSrcScene,mDstScene);

	}
}

void CSceneEffect::Start( CScene* src , CScene* dest )
{
	mSrcScene = src;
	mDstScene = dest;

	const CBound& srcBound = src->Bound();
	const CBound& dstBound = dest->Bound();

	mSrcBuffer = NEW_LEAKCHECK CImageBuffer;
	mSrcBuffer->Initialize(srcBound.Width() , srcBound.Height() , false);
	CGraphics graphic(mSrcBuffer);
	src->Draw(&graphic);

	mDstBuffer = NEW_LEAKCHECK CImageBuffer;
	mDstBuffer->Initialize(srcBound.Width() , srcBound.Height() , false);
	graphic.Initialize(mDstBuffer);
	dest->Draw(&graphic);

	mTimerId = sUIFrame.GetTimerMgr()->CreateTimer(this,mInterval);
}

