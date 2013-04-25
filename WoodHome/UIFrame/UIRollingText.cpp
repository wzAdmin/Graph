#include "UIRollingText.h"
#include "Graphics.h"
#include "FontConfig.h"
#include "UIFrame.h"
#include "TimerManager.h"

CUIRollingText::CUIRollingText(void):
mRolling(false),
mTimerid(InvalidTimer),
mInited(false),
mRollFrequency(20)
{
}

CUIRollingText::~CUIRollingText(void)
{
	sUIFrame.GetTimerMgr()->RemoveTimer(mTimerid);
}

void CUIRollingText::Text( const std::wstring& wcs )
{
	mText = wcs;
	mInited=false;
}

void CUIRollingText::Draw( CGraphics* pGraphic )
{
	Init(pGraphic);
	if(mRolling)
	{
		const Font& ft = *sFontConfig.GetFont(mFontID);
		mCurCharWidth = pGraphic->GetCharWidth(mText[mIndex] , ft);
		CBound bd = Bound();
		Parent()->Absolute(bd);
		bd.Left(bd.Left() - mOffset);
		pGraphic->DrawTextW(mText.c_str() + mIndex ,bd,ft,LEFT);
	}
	else
		CUITextView::Draw(pGraphic);
}

void CUIRollingText::Init( CGraphics* pGraphic)
{
	if(mInited)
		return ;
	mInited = true;
	int TextWidth = 0;
	const Font& ft = *sFontConfig.GetFont(mFontID);
	for (unsigned int i = 0 ; i < mText.size() ; i ++)
	{
		TextWidth += pGraphic->GetCharWidth(mText[i] , ft);
		if(TextWidth > Bound().Width())
		{
			mIndex = 0;
			mOffset = 0;
			mRolling = true;
			sUIFrame.GetTimerMgr()->CreateTimer(this , mRollFrequency);
			break;
		}
	}
}

void CUIRollingText::Load( const slim::XmlNode* node )
{
	CUITextView::Load(node);
}

void CUIRollingText::OnTimer( TimerID timerid )
{
	mOffset += 5;
	if(mCurCharWidth <= mOffset)
	{
		mIndex++;
		mOffset -= mCurCharWidth;
		if(mIndex == mText.size())
		{
			mOffset = 0;
			mIndex = 0;
		}
	}
	DrawToWindow();
}
