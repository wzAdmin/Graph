#pragma once
#include "sceneeffect.h"

class CEffectFadeto :
	public CSceneEffect
{
public:
	CEffectFadeto(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic);
	~CEffectFadeto(void);
private:
	virtual void Effect();
};

