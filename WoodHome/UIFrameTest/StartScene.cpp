#include "StartScene.h"
#include "Trace.h"
#include "UIButton.h"
#include "UIFrame.h"

CStartScene::CStartScene(void)
{
}

CStartScene::~CStartScene(void)
{
}

void CStartScene::OnBtn1Click()
{
	DebugTrace("notify Sucessfull\n");
	sUIFrame.StartWindow(Window_Main);
}

void CStartScene::Load( const slim::XmlNode* node )
{
	CScene::Load(node);
	CUIButton* pbtn1 = (CUIButton*)get("btn1");
	pbtn1->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn1Click);
}
