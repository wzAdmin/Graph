#pragma once
#include "uiobject.h"
#include "resource_image.h"
#include <string>
enum ButtonStaus
{
	BS_Normal,
	BS_Focus,
	BS_Disable
};
class CUIButton :
	public CUIObject
{
public:
	static CUIObject* Create(){return new CUIButton;}
	CUIButton(void);
	~CUIButton(void);
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual bool OnLBtnDown(int x ,int y);
	virtual bool OnLBtnUp(int x ,int y);
	virtual void Load(const slim::XmlNode* node);
private:
	SourceID mNormalImage;
	SourceID mFocusImage;
	SourceID mDisableImage;
	ButtonStaus mBtnStatus;
	std::wstring mText;
};

