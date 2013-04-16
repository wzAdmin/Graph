#pragma once
#include "UILayer.h"
class CUIWindow;
class UI_API CScene :
	public CUILayer
{
public:
	CScene(CUIWindow* wnd = NULL);
	~CScene(void);
public:
	virtual void Draw(CGraphics* pGraphic);
	void Goto();
	void DrawToWindow();
private:
	CUIWindow* mWind;
};

