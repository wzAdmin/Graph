
#include "UITextView.h"
#include "Graphics.h"
#include "FontConfig.h"
#include "UIFrame.h"
#include "TimerManager.h"
#include "SlimXml.h"
#include "CommonFun.h"

CUITextView::CUITextView(void):
mAutoRolling(false),
mTimerid(InvalidTimer),
mInited(false),
mRollFrequency(100),
mIsWrap(true),
mRowSpace(0.2f),
mFontID(0),
malign(CENTER)
{
}

CUITextView::~CUITextView(void)
{
	sUIFrame.GetTimerMgr()->RemoveTimer(mTimerid);
}

void CUITextView::Text( const std::wstring& wcs )
{
	mText = wcs;
	mInited=false;
}

void CUITextView::Draw( CGraphics* pGraphic )
{
 	Init(pGraphic);
	if(mIsWrap)
		WrapDraw(pGraphic);
	else
		SingleLineDraw(pGraphic);
}

void CUITextView::Init( CGraphics* pGraphic)
{
	if(mInited)
	{
		if(InvalidTimer == mTimerid && mAutoRolling)
			mTimerid = sUIFrame.GetTimerMgr()->CreateTimer(this , mRollFrequency);
		return ;
	}
	mInited = true;
	if(mIsWrap)
		return Wrap(pGraphic);
	int TextWidth = 0;
	const Font& ft = *sFontConfig.GetFont(mFontID);
	for (unsigned int i = 0 ; i < mText.size() ; i ++)
	{
		TextWidth += pGraphic->GetCharWidthW(mText[i] , ft);
		if(TextWidth > Bound().Width())
		{
			mIndex = 0;
			mOffset = Bound().Right();
			mAutoRolling &= true;
			if(mAutoRolling)
				mTimerid = sUIFrame.GetTimerMgr()->CreateTimer(this , mRollFrequency);
			break;
		}
	}
}

void CUITextView::Load( const slim::XmlNode* node )
{	
	CUIObject::Load(node);
	mText = AnsiToWstring(node->readAttributeAsString("text"));
	mRowSpace = node->readAttributeAsFloat("space",0.2f);
	mIsWrap = node->readAttributeAsBool("wrap");
	mAutoRolling = node->readAttributeAsBool("autoroll");
	mFontID = node->readAttributeAsInt("font");
}

void CUITextView::OnTimer( TimerID timerid )
{
	if(!IsRealVisible())
	{
		sUIFrame.GetTimerMgr()->RemoveTimer(mTimerid);
		mTimerid = InvalidTimer;
		return;
	}
	if(mIsWrap)
		WrapRoll();
	else
		SingleLineRoll();
	DrawToWindow();
}

void CUITextView::Wrap(CGraphics* pGraphic ,int index/* = 0*/)
{
	if(0==index)
	{
		mWrapIndex.clear();
		mOffset = Bound().Bottom();
		mIndex=0;
	}
	int TextWidth = 0;
	const Font& ft = *sFontConfig.GetFont(mFontID);
	mCurCharSize = int(ft.height * ( 1 + mRowSpace));
	mWrapIndex.push_back(0);
	for(unsigned int i = index ; i <  mText.size();i++)
	{
		int chwidth = pGraphic->GetCharWidthW(mText[i] , ft);
		TextWidth += chwidth;
		if(TextWidth > Bound().Width())
		{
			TextWidth =  chwidth;
			mWrapIndex.push_back(i);
		}
	}
	mWrapIndex.push_back(mText.size());
	int lines = int(mWrapIndex.size()) - 1;
	//only a single line
	//
	if(1 == lines)
	{
		mIsWrap = false;
		mAutoRolling = false;
		return ;
	}
	//
	//the text can be showed in one page ,do not need roll
	if(Bound().Height() / mCurCharSize >= lines)
	{
		mOffset = (Bound().Top() + Bound().Bottom()  - mCurCharSize * lines) / 2;
		mAutoRolling = false;
	}
	else
	{
		mAutoRolling &= true;
		if(mAutoRolling)
			mTimerid = sUIFrame.GetTimerMgr()->CreateTimer(this , mRollFrequency);
	}
}

void CUITextView::WrapDraw( CGraphics* pGraphic )
{
	const Font& ft = *sFontConfig.GetFont(mFontID);
	int left = Bound().Left();
	int top = mOffset ;

	int index = mIndex;
	while (top < Bound().Bottom() && index < int(mWrapIndex.size()) - 1)
	{
		top += mCurCharSize;
		CPosition pt(left,top);
		if(Parent())
			pt = Parent()->Absolute(left , top);
		std::wstring str = mText.substr(mWrapIndex[index],mWrapIndex[index + 1] - mWrapIndex[index]);
		index++;
		pGraphic->DrawTextW(str.c_str(),pt.X(),pt.Y(),ft);
	}
}

void CUITextView::WrapRoll()
{
	mOffset -= 3;
	if(Bound().Top() - mCurCharSize >= mOffset)
 	{
 		mIndex++;
 		mOffset += mCurCharSize;
 		if(mIndex == mWrapIndex.size() - 1)
 		{
 			mOffset = Bound().Bottom();
 			mIndex = 0;
 		}
 	}
}

void CUITextView::SingleLineDraw( CGraphics* pGraphic )
{
	const Font& ft = *sFontConfig.GetFont(mFontID);
 	if(mAutoRolling)
 	{
 		mCurCharSize = pGraphic->GetCharWidthW(mText[mIndex] , ft);
		CBound bd = Bound();
		bd.Left(mOffset);
		if(Parent())
 			Parent()->Absolute(bd);
 		pGraphic->DrawTextW(mText.c_str() + mIndex ,bd,ft,LEFT);
 	}
 	else
	{
		CBound bd =Bound();
		if(Parent())
			Parent()->Absolute(bd);
		pGraphic->DrawTextW(mText.c_str(),bd,ft,malign);
	}
}

void CUITextView::SingleLineRoll()
{
 	mOffset -= 3;
 	if(Bound().Left() - mCurCharSize >=mOffset)
 	{
 		mIndex++;
 		mOffset += mCurCharSize;
 		if(mIndex == mText.size())
 		{
 			mOffset = Bound().Right();
 			mIndex = 0;
 		}
 	}
}
