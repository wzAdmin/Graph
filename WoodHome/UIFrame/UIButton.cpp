#include "UIButton.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "ImageResouceMgr.h"
#include "SlimXml.h"

CUIButton::CUIButton(void):
mBtnStatus(BS_Normal),
mDisableImage(Invalid),
mFocusImage(Invalid),
mNormalImage(Invalid)
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
		Font ft;
		ft.color = CRGB(123,231,12);
		ft.height = 15;
		ft.width = 20;
		CBound bd = Bound();
		Parent()->SelfToParent(bd);
		pGraphic->DrawImage_Repeat(pBuffer,CBound(0,pBuffer->Width()-1,0,pBuffer->Height()-1),bd);
		pGraphic->DrawTextW(mText.c_str(),bd,ft,CENTER);
	}
}

bool CUIButton::OnLBtnDown( int x ,int y )
{
	mBtnStatus = BS_Focus;
	DrawToWindow();
	return true;
}

bool CUIButton::OnLBtnUp( int x ,int y )
{
	mBtnStatus = BS_Normal;
	DrawToWindow();
	return true;
}

void CUIButton::Load( const slim::XmlNode* node )
{
	CUIObject::Load(node);
	mBtnStatus = BS_Normal;
	mDisableImage = SourceID(node->readAttributeAsInt("Disale",Invalid));
	mFocusImage = SourceID(node->readAttributeAsInt("Focus",Invalid));
	mNormalImage = SourceID(node->readAttributeAsInt("Normal",Invalid));
	//mText = node->readAttributeAsString("Text","");
	mText = L"Œ“ «∞¥≈•";
}


