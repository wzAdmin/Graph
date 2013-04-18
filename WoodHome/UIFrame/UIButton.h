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
typedef void (CUIObject::*OnBtnDown)();
typedef void (CUIObject::*OnBtnUp)();
typedef void (CUIObject::*OnBtnClick)();
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
	virtual bool OnMouseMove(int x ,int y){return true;}
	//
	//<Button x="100" y = "100" width = "150" height = "50" Visible = "true" 
	//Order = "0" Focus = "1" Normal = "2" Disable = "3" Text = "ÎÒÊÇ°´Å¥" Font = "3"/>
	//
	virtual void Load(const slim::XmlNode* node);
	void SetText(const std::wstring& text){mText = text;}
protected:
	virtual void OnFocusOut();
private:
	SourceID mNormalImage;
	SourceID mFocusImage;
	SourceID mDisableImage;
	ButtonStaus mBtnStatus;
	std::wstring mText;
	int mFontID;
	OnBtnClick mOnClickFunc;
	CUIObject* mListener;
};

