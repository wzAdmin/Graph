#include "UIButton.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "ImageResouceMgr.h"
#include "SlimXml.h"
#include "CommonFun.h"
#include "FontConfig.h"

CUIButton::CUIButton(void):
mBtnStatus(BS_Normal),
mDisableImage(Invalid),
mFocusImage(Invalid),
mNormalImage(Invalid),
mOnClickFunc(NULL),
mListener(NULL)
{
}


CUIButton::~CUIButton(void)
{
}

void CUIButton::Draw( CGraphics* pGraphic )
{
	CImageBuffer* pBuffer = NULL;
	switch (mBtnStatus)
	{
	case BS_Disable:
		pBuffer = sImageResource.GetImage(mDisableImage);
		break;
	case BS_Focus:
		pBuffer = sImageResource.GetImage(mFocusImage);
		break;
	default:
		pBuffer = sImageResource.GetImage(mNormalImage);
	}
	if(pBuffer)
	{
		CBound bd = Bound();
		Parent()->SelfToParent(bd);
		pGraphic->DrawImage_Repeat(pBuffer,&bd);
		pGraphic->DrawTextW(mText.c_str(),bd,*sFontConfig.GetFont(mFontID),CENTER);
	}
}

bool CUIButton::OnLBtnDown( int x ,int y )
{
	if(BS_Disable != mBtnStatus)
	{
		mBtnStatus = BS_Focus;
		DrawToWindow();
	}
	return true;
}

bool CUIButton::OnLBtnUp( int x ,int y )
{
	if(BS_Disable != mBtnStatus)
	{
		if(BS_Focus == mBtnStatus)
		{
			mBtnStatus = BS_Normal;
			DrawToWindow();
			if(mListener && mOnClickFunc)
				(mListener->*mOnClickFunc)();
		}
	}
	return true;
}

void CUIButton::Load( const slim::XmlNode* node )
{
	CUIObject::Load(node);
	mBtnStatus = BS_Normal;
	mDisableImage = SourceID(node->readAttributeAsInt("disable",Invalid));
	mFocusImage = SourceID(node->readAttributeAsInt("focus",Invalid));
	mNormalImage = SourceID(node->readAttributeAsInt("normal",Invalid));
	mText = AnsiToWstring(node->readAttributeAsString("text",""));
	mFontID = node->readAttributeAsInt("font");
}

void CUIButton::OnFocusOut()
{
	if(BS_Focus == mBtnStatus)
	{
		mBtnStatus = BS_Normal;
		DrawToWindow();
	}
}


