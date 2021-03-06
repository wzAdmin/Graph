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
typedef void (CUIObject::*OnBtnClick)();
class UI_API CUIButton :
	public CUIObject
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUIButton;}
	CUIButton(void);
	~CUIButton(void);
public:
	void SetStatus(ButtonStaus bs){mBtnStatus = bs;}
	void AddClickListen(CUIObject* pobj,OnBtnClick func){mListener = pobj ; mOnClickFunc=func;}
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual bool OnLBtnDown(int x ,int y);
	virtual bool OnLBtnUp(int x ,int y);
	virtual bool OnMouseMove(int x ,int y){return BS_Focus == mBtnStatus;}
	//
	//<Button x="100" y = "100" width = "150" height = "50" Visible = "true" 
	//Order = "0" Focus = "1" Normal = "2" Disable = "3" Text = "���ǰ�ť" Font = "3"/>
	//
	virtual void Load(const slim::XmlNode* node);
	void SetText(const std::wstring& text){mText = text;}

protected:
	virtual void OnFocusOut(CUIObject* newFocus);
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

