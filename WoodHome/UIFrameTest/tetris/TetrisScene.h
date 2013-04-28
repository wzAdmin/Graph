#pragma once
#include "scene.h"
class CTetrisScene :
	public CScene
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CTetrisScene;}
	CTetrisScene(void);
	~CTetrisScene(void);
private:
	virtual void OnLoad();
	virtual void DrawSelf(CGraphics* pGraphic);
	void OnBack();
};

