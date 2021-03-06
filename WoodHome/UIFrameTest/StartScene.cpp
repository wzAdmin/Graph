#include "StartScene.h"
#include "Trace.h"
#include "UIButton.h"
#include "UIFrame.h"
#include "SceneManager.h"

CStartScene::CStartScene(void)
{
}

CStartScene::~CStartScene(void)
{
	sUIFrame.GetTimerMgr()->RemoveTimer(mtimerid);
}

void CStartScene::OnBtn1Click()
{
	DebugTrace(Trace_Info,"notify Sucessfull\n");
	Goto(SCENE_DrawText);
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
	MsgBoxParam arg;
	arg.listner = this;
	arg.msg = L"确定退出程序？你真的确定吗？还要多搞点才会换行 擦";
	mWind->GetSceneMgr()->GotoAsDialog(SCENE_MsgBox,&arg);
}

void CStartScene::OnTimer( TimerID timerid )
{
	//DebugTrace(Trace_Normal,"Timer come %d %d\n",timerid,mtimerid);
}

void CStartScene::OnBtn5Click()
{
	Goto(SCENE_EffectTest,NULL,Effect_FadeTo);
}

void CStartScene::OnLoad()
{
	CUIButton* pbtn1 = (CUIButton*)get("btn1");
	pbtn1->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn1Click);
	CUIButton* pbtn2 = (CUIButton*)get("btn2");
	pbtn2->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn2Click);
	CUIButton* pbtn3 = (CUIButton*)get("btn3");
	pbtn3->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn3Click);
	CUIButton* pbtn4 = (CUIButton*)get("btn4");
	pbtn4->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn4Click);
	CUIButton* pbtn5 = (CUIButton*)get("btn5");
	pbtn5->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtn5Click);
	CUIButton* pbtnlist = (CUIButton*)get("list");
	pbtnlist->AddClickListen(this,(OnBtnClick)&CStartScene::OnBtnListClick);
	CUIButton* pbtntetris = (CUIButton*)get("tetris");
	pbtntetris->AddClickListen(this,(OnBtnClick)&CStartScene::OnTetrisClick);
	mtimerid = sUIFrame.GetTimerMgr()->CreateTimer(this,100);
}

void CStartScene::OnBtnListClick()
{
	Goto(SCENE_ListTest);
}

void CStartScene::OnOK()
{
	sUIFrame.Exit();
}

void CStartScene::OnCancel()
{

}

void CStartScene::OnTetrisClick()
{
	Goto(SCENE_Tetris);
}
