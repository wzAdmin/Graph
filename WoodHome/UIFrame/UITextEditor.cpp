#include "UITextEditor.h"
#include "UIFrame.h"
#include "Graphics.h"
#include "FontConfig.h"

CUITextEditor::CUITextEditor(void) : mCurosTimer(InvalidTimer),mCurosPositoin(0),mIsCurosShowing(false)
{
	malign = LEFT;
}


CUITextEditor::~CUITextEditor(void)
{
}

bool CUITextEditor::OnInputChar( const wchar_t* wcs,int len )
{
	if(!mIsInputMode)
		return false;
	mText.append(wcs,len);
	mCurosPositoin += len;
	DrawToWindow();
	return true;
}

bool CUITextEditor::OnMouseMove( int x ,int y )
{
	return true;
}

void CUITextEditor::OnFocusOut(CUIObject* newFocus)
{
	if(newFocus && newFocus->InputMode())
	{
		LoseFucos();
	}
}

bool CUITextEditor::OnLBtnDown( int x ,int y )
{
	mIsInputMode = true;
	mCurosTimer = sUIFrame.GetTimerMgr()->CreateTimer(this,500);
	return true;
}

bool CUITextEditor::OnLBtnUp( int x ,int y )
{
	return true;
}

void CUITextEditor::OnTimer( TimerID timerid )
{
	if(timerid != mCurosTimer)
		return;
	if(!IsRealVisible())
	{
		LoseFucos();
		return;
	}
	mIsCurosShowing = !mIsCurosShowing;
	DrawToWindow();
}

void CUITextEditor::Draw( CGraphics* pGraphic )
{
	CBound bd = Bound();
	if(mParent)
		mParent->Absolute(bd);
	pGraphic->FillBoud(bd , CRGB(255,255,255));
	CUITextView::Draw(pGraphic);
	if(mIsCurosShowing)
		DrawCuros(pGraphic);
}

void CUITextEditor::LoseFucos()
{
	mIsInputMode = false;
	sUIFrame.GetTimerMgr()->RemoveTimer(mCurosTimer);
	mCurosTimer = InvalidTimer;
	mIsCurosShowing = false;
}

void CUITextEditor::DrawCuros( CGraphics* pGraphic )
{
	int left = 0;
	const Font& ft = *sFontConfig.GetFont(mFontID);
	for (int i = 0 ; i < mCurosPositoin ; i ++)
	{
		left += pGraphic->GetCharWidthW(mText[i] , ft);
	}
	int top = (Bound().Height()  - ft.height) / 2;
	CBound bd(left,left,top,top+ft.height);
	Absolute(bd);
	pGraphic->FillBoud(bd , CRGB(0,0,0));
}
