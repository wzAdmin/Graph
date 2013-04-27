#include "UIMsgBox.h"
#include "UITextView.h"
#include "UIButton.h"
#include "UIWindow.h"

CUIMsgBox::CUIMsgBox(void):mListner(NULL)
{
}

CUIMsgBox::~CUIMsgBox(void)
{
}

void CUIMsgBox::OnShow( void* data /* = NULL */ )
{
	if(data)
	{
		MsgBoxParam* arg = (MsgBoxParam*)data;
		mListner = arg->listner;
		CUITextView* text = (CUITextView*)get("msg");
		text->Text(arg->msg);
	}
}

void CUIMsgBox::OnOK()
{
	Visible(false);
	mWind->DrawToWindow();
	if(mListner)
		mListner->OnOK();
}

void CUIMsgBox::OnCancel()
{
	Visible(false);
	mWind->DrawToWindow();
	if(mListner)
		mListner->OnCancel();
}

void CUIMsgBox::OnLoad()
{
	CUIButton* btn = (CUIButton*)get("ok");
	btn->AddClickListen(this,(OnBtnClick)&CUIMsgBox::OnOK);
	btn = (CUIButton*)get("cancel");
	btn->AddClickListen(this , (OnBtnClick)&CUIMsgBox::OnCancel);
}
