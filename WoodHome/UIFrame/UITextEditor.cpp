#include "UITextEditor.h"
#include "UIFrame.h"
#include "Graphics.h"
#include "FontConfig.h"
#include "Scene.h"

CUITextEditor::CUITextEditor(void) :
mCurosTimer(InvalidTimer),
mCurosIndex(0),
mIsCurosShowing(false),
mMaxInputCount(sDefaultCount)
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
	if(DealSpecialChar(wcs[0]))
		return true;
	if(mText.size() == mMaxInputCount)
		return true;
	len = MIN(len , int(mMaxInputCount - mText.size()));
	mText.append(wcs,len);
	mCurosIndex += len;
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
	CScene* root = (CScene*)Root();
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
	SetCurosPosition(pGraphic);
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
	const Font& ft = *sFontConfig.GetFont(mFontID);
	CBound bd(mCurosPosition.X(),mCurosPosition.X(),
		mCurosPosition.Y() - ft.height ,mCurosPosition.Y());
	Absolute(bd);
	pGraphic->FillBoud(bd , CRGB(0,0,0));
}

void CUITextEditor::SetIMEPos()
{
	CPosition pt = Absolute(mCurosPosition.X() , mCurosPosition.Y());
	((CScene*)Root())->SetIMEPos(pt.X() , pt.Y());
}

void CUITextEditor::SetCurosPosition(CGraphics* pGraphic)
{
	malign = LEFT;
	int left = 0;
	const Font& ft = *sFontConfig.GetFont(mFontID);
	for (int i = 0 ; i < mCurosIndex ; i ++)
	{
		left += pGraphic->GetCharWidthW(mText[i] , ft);
	}
	if(left > Bound().Width())
	{
		left = Bound().Width() - 1;
		malign = RIGHT;
	}
	int top = (Bound().Height()  - ft.height) / 2;
	mCurosPosition.X(left);
	mCurosPosition.Y(top + ft.height);
	SetIMEPos();
}

bool CUITextEditor::DealSpecialChar( wchar_t ch )
{
	switch (ch)
	{
		// 27 Esc
	case 27:
	case L'\n':
	case L'\r':
	case L'\t':
	case L'\a':
	case L'\f':
	case L'\v':
		return true;
	case L'\b':
		Backspace();
		return true;
	}
	return false;
}

void CUITextEditor::Backspace()
{
	if(!mText.empty())
	{
		mText.erase(--mCurosIndex);
		DrawToWindow();
	}
}

