#include "Scene.h"
#include "UIWindow.h"
CScene::CScene(CUIWindow* wnd /*= NULL*/):mWind(wnd)
{
}


CScene::~CScene(void)
{
}

void CScene::Draw( CGraphics* pGraphic )
{
	CUILayer::Draw(pGraphic);
}

void CScene::DrawToWindow()
{
	mWind->DrawToWindow();
}
