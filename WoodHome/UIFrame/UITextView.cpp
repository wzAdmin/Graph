#include "UITextView.h"
#include "Graphics.h"
#include "FontConfig.h"
#include "SlimXml.h"
#include "CommonFun.h"

CUITextView::CUITextView(void): mFontID(0)
{
}


CUITextView::~CUITextView(void)
{
}

void CUITextView::Load( const slim::XmlNode* node )
{
	CUIObject::Load(node);
	mText = AnsiToWstring(node->readAttributeAsString("text"));
	mFontID = node->readAttributeAsInt("font");
}

void CUITextView::Draw( CGraphics* pGraphic )
{

	pGraphic->DrawTextW(mText.c_str(),Bound(),*sFontConfig.GetFont(mFontID),CENTER);
}
