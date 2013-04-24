#pragma once
#include "uiobject.h"
class UI_API CUITextView :
	public CUIObject
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUITextView;}
	CUITextView(void);
	~CUITextView(void);
private:
	virtual void Load(const slim::XmlNode* node);
	virtual void Draw(CGraphics* pGraphic);
};

