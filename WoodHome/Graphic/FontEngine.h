#pragma once
#include "Bound.h"
#include "FontCache.h"
#include "GraphicType.h"

class GRAPHIC_API CFontEngine
{
private:
	CFontEngine(void);
	~CFontEngine(void);
public:
	static CFontEngine& Instance();
	bool Init(const char* fontpath);
	void Destroy();
	FontImage GetFont(unsigned short charCode,unsigned int width , unsigned int height);
private:
	FT_Library mFtlib;
	FT_Face mFace;
	CFontCache* mCache;
};
#define sFontEngine CFontEngine::Instance()

