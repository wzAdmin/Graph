#include "TetrisScene.h"
#include "UIButton.h"
#include "Trace.h"
#include "Graphics.h"

CTetrisScene::CTetrisScene(void)
{
}


CTetrisScene::~CTetrisScene(void)
{
}

void CTetrisScene::OnBack()
{
	Back();
}

void CTetrisScene::OnLoad()
{
	CUIButton* btnback = (CUIButton*)get("back");
	btnback->AddClickListen(this,(OnBtnClick)&CTetrisScene::OnBack);
}

void CTetrisScene::DrawSelf( CGraphics* pGraphic )
{
	CBound dstbd = Bound();
	if(mParent)
		mParent->Absolute(dstbd);
	pGraphic->FillBoud(dstbd,CRGB(123,100,53));
}

