#include "EffectFadeto.h"
#include "ImageBuffer.h"
#include "Graphics.h"

CEffectFadeto::CEffectFadeto(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic):
CSceneEffect(listner , interval , Frames , pGraphic)
{
}


CEffectFadeto::~CEffectFadeto(void)
{
}

void CEffectFadeto::Effect()
{
	unsigned char alpha = unsigned char((mCurFrames<<5) / mTotaolFrames);
	CBound bound(0 , mSrcBuffer->Width() - 1, 0 ,mSrcBuffer->Height()-1);
	mGraphics->DrawImage_Repeat(mSrcBuffer,bound , bound);
	mGraphics->DrawImage_Repeat(mDstBuffer,alpha,NULL,NULL);
}
