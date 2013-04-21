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
	Goto(SCENE_DrawText);
}

void CStartScene::Load( const slim::XmlNode* node )
{
	CScene::Load(node);
	CUIButton* pbtn1 = (CUIButton*)get("btn1");
	pbtn1->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn1Click);
	CUIButton* pbtn2 = (CUIButton*)get("btn2");
	pbtn2->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn2Click);
	CUIButton* pbtn3 = (CUIButton*)get("btn3");
	pbtn3->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn3Click);
	CUIButton* pbtn4 = (CUIButton*)get("btn4");
	pbtn4->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn4Click);
	mtimerid = sUIFrame.GetTimerMgr()->CreateTimer(this,100);
}

void CStartScene::OnBtn3Click()
{
	sUIFrame.StartWindow(Main_Window);
}

void CStartScene::OnBtn2Click()
{
	Goto(SCENE_ImageTest);
}

void CStartScene::OnBtn4Click()
{
	sUIFrame.Exit();
}

void CStartScene::OnTimer( TimerID timerid )
{
	DebugTrace("Timer come %d %d\n",timerid,mtimerid);
}
