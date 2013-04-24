#pragma once
#include "scene.h"

class CEffectTest :
	public CScene
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CEffectTest;}
	CEffectTest(void);
	~CEffectTest(void);
private:
	virtual void OnLoad();
	void OnBtnbackClick();
	void OnBtnfadetoClick();
};
