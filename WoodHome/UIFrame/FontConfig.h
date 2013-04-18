#pragma once
#include "GraphicType.h"
class CFontConfig
{
private:
	CFontConfig(void);
	~CFontConfig(void);
	void Load();
public:
	static CFontConfig& Instance();
public:
	 const Font* GetFont(int id);
private:
	Font* mFonts;
	int mFontCount;
};

#define sFontConfig CFontConfig::Instance()
