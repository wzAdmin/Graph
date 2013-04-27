#include "ListScene.h"
#include "UIList.h"
#include "TestAdapter.h"
#include "UIButton.h"

CListScene::CListScene(void):mListAdapter(NULL)
{

}

CListScene::~CListScene(void)
{
	if(mListAdapter)
		DELETE_LEAKCHECK(mListAdapter);
}

void CListScene::OnNext()
{
	mList->Next();
	if(!mList->CanPrev())
		mPrev->SetStatus(BS_Disable);
	else
		mPrev->SetStatus(BS_Normal);
	if(!mList->CanNext())
		mNext->SetStatus(BS_Disable);
	else
		mNext->SetStatus(BS_Normal);
	mNext->DrawToWindow();
	mPrev->DrawToWindow();
}

void CListScene::OnPrev()
{
	mList->Prev();	
	if(!mList->CanPrev())
		mPrev->SetStatus(BS_Disable);
	else
		mPrev->SetStatus(BS_Normal);
	if(!mList->CanNext())
		mNext->SetStatus(BS_Disable);
	else
		mNext->SetStatus(BS_Normal);
	mNext->DrawToWindow();
	mPrev->DrawToWindow();
}

void CListScene::OnLoad()
{
	mListAdapter  = NEW_LEAKCHECK CTestAdapter;
	mList = (CUIList*)get("list");
	mPrev = (CUIButton*)get("btn5");
	mNext = (CUIButton*)get("btn4");
	((CUIButton*)get("back"))->AddClickListen(this,(OnBtnClick)&CListScene::OnBack);
	mPrev->AddClickListen(this,(OnBtnClick)&CListScene::OnPrev);
	mNext->AddClickListen(this,(OnBtnClick)&CListScene::OnNext);
	mList->SetData(mListAdapter);
	if(!mList->CanPrev())
		mPrev->SetStatus(BS_Disable);
	else
		mPrev->SetStatus(BS_Normal);
	if(!mList->CanNext())
		mNext->SetStatus(BS_Disable);
	else
		mNext->SetStatus(BS_Normal);
}

void CListScene::OnBack()
{
	Back();
}
