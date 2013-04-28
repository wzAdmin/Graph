#pragma once
#include "uiobject.h"
#include<vector>
class UI_API CUIContainer :
	public CUIObject
{
public:
	CUIContainer(void);
	virtual ~CUIContainer(void);
public:
	void AddChild(CUIObject* child);
	void RemoveChild(CUIObject* child);
	void Clear();
public:
	virtual bool OnInputChar(const wchar_t* wcs,int len);
	virtual bool OnLBtnDown(int x ,int y);
	virtual bool OnLBtnUp(int x ,int y);
	virtual bool OnMouseMove(int x ,int y);
	virtual bool OnRBtnDown(int x ,int y);
	virtual bool OnRBtnUp(int x ,int y);
	virtual bool OnKey(const KeyEvent& e);
protected:
	virtual void Draw(CGraphics* pGraphic);
	virtual void DrawSelf(CGraphics* pGraphic) = 0;
	virtual void LoadSelf(const slim::XmlNode* node) = 0;
	virtual void Load(const slim::XmlNode* node);
	virtual CUIObject* get(const std::string& name);
protected:
	std::vector<CUIObject*> mChilds;
	CUIObject* mFcousedObj;
};

