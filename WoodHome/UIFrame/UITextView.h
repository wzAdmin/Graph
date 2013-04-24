#pragma once
#include <string>
#include "uiobject.h"

class UI_API CUITextView :
	public CUIObject
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUITextView;}
	CUITextView(void);
	~CUITextView(void);
public:
	void Text(const std::wstring& wcs){mText = wcs;}
	const std::wstring& Text() const {return mText;}
private:
	virtual void Load(const slim::XmlNode* node);
	virtual void Draw(CGraphics* pGraphic);
private:
	std::wstring mText;
	int mFontID;
};

