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
protected:
	virtual void Draw(CGraphics* pGraphic);
	virtual void DrawSelf(CGraphics* pGraphic) = 0;
	virtual void LoadSelf(const slim::XmlNode* node) = 0;
	virtual void Load(const slim::XmlNode* node);
	virtual bool DealMessage(const SystemMessage& message);
private:
	std::vector<CUIObject*> mChilds;
};

