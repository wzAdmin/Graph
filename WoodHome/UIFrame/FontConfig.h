#pragma once
#include "GraphicType.h"
#include "UItype.h"
#include "resource_image.h"
class UI_API CFontConfig
{
private:
	CFontConfig(void);
	~CFontConfig(void);
public:
	void Load(SourceID id);
	static CFontConfig& Instance();
public:
	 const Font* GetFont(int id);
private:
	Font* mFonts;
	int mFontCount;
};

#define sFontConfig CFontConfig::Instance()
