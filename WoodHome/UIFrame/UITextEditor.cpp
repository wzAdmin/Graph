#include "UITextEditor.h"
#include "UIFrame.h"

CUITextEditor::CUITextEditor(void) : mCurosTimer(InvalidTimer)
{
}


CUITextEditor::~CUITextEditor(void)
{
}

bool CUITextEditor::OnInputChar( const wchar_t* wcs,int len )
{
	if(!mIsInputMode)
		return false;
	mText.append(wcs,len);
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
	mCurosTimer = sUIFrame.GetTimerMgr()->CreateTimer(this,100);
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
	if(mIsCurosShowing)
		CUITextView::Draw(pGraphic);
}

void CUITextEditor::LoseFucos()
{
	mIsInputMode = false;
	sUIFrame.GetTimerMgr()->RemoveTimer(mCurosTimer);
	mCurosTimer = InvalidTimer;
}
