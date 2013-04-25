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

void CScene::DrawToWindow(const CBound* bd /*= NULL*/)
{
	mWind->DrawToWindow(bd);
}

void CScene::Goto( SourceID toScene,void* data /*= NULL*/,EffectType effect /*= Effect_Invalid*/ )
{
	mWind->GetSceneMgr()->GoTo(toScene ,this , data , effect);
}

void CScene::Back(void* data /*= NULL*/,EffectType effect /*= Effect_Invalid*/ )
{
	mWind->GetSceneMgr()->Back(data,effect);
}

void CScene::Load( const slim::XmlNode* node )
{
	CUILayer::Load(node);
	OnLoad();
}
