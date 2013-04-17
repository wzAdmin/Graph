#include "Scene.h"
#include "UIWindow.h"
#include "SceneManager.h"
CScene::CScene()
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

void CScene::Goto( SourceID toScene )
{
	mWind->GetSceneMgr()->GoTo(toScene ,this);
}
