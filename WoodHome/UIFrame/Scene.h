#pragma once
#include "UILayer.h"
class CUIWindow;
class UI_API CScene :
	public CUILayer
{
	friend class CSceneManager;
public:
	CScene();
	~CScene(void);
	static CUIObject* Create(){return new CScene;}
public:
	virtual void Draw(CGraphics* pGraphic);
	void SetWind(CUIWindow* Wnd){mWind = Wnd;}
	void Goto(SourceID toScene);
	void DrawToWindow();
private:
	CUIWindow* mWind;
};

