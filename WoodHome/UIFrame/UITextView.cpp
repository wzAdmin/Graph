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
	CBound bd = Bound();
	Parent()->Absolute(bd);
	pGraphic->DrawTextW(mText.c_str(),bd,*sFontConfig.GetFont(mFontID),CENTER);
}
