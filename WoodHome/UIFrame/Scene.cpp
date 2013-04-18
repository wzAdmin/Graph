#include "Scene.h"
#include "UIWindow.h"
#include "SceneManager.h"
CScene::CScene():mFrom(NULL),mNotifyFunc(NULL)
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

void CScene::Goto( SourceID toScene,void* data /*= NULL*/ )
{
	mWind->GetSceneMgr()->GoTo(toScene ,this,data);
}

void CScene::Back()
{
	mWind->GetSceneMgr()->Back();
}
