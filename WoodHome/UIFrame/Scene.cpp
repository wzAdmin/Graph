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
	CBound dstbd = Bound();
	if(bd)
		dstbd = *bd;
	SelfToParent(dstbd);
	mWind->DrawToWindow(&dstbd);
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

void CScene::SetIMEPos( int x , int y )
{
	mWind->SetIMEPos(x , y);
}
