#pragma once
#include "uicontainer.h"
#include "resource_image.h"
class UI_API CUILayer :
	public CUIContainer
{
public:
	CUILayer(void);
	~CUILayer(void);
public:
	void LoadFromFile(SourceID id);
protected:
	virtual void LoadSelf(const slim::XmlNode* node);
	virtual void Load(const slim::XmlNode* node);
	virtual void DrawSelf(CGraphics* pGraphic);
private:
	SourceID mImageId;
};

