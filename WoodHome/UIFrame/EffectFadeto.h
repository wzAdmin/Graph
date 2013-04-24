#pragma once
#include "sceneeffect.h"
#include "Memory_Check.h"

class CEffectFadeto :
	public CSceneEffect
{
public:
	static CSceneEffect* Create(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic)
	{return NEW_LEAKCHECK CEffectFadeto(listner,interval,Frames,pGraphic);}
public:
	CEffectFadeto(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic);
	~CEffectFadeto(void);
private:
	virtual void Effect();
};

