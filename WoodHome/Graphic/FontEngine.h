#pragma once
#include "Bound.h"
#include "FontCache.h"

class CFontEngine
{
private:
	CFontEngine(void);
	~CFontEngine(void);
public:
	static CFontEngine& Instance();
	FontImage GetFont(unsigned short charCode,unsigned int width , unsigned int height);
private:
	FT_Library mFtlib;
	FT_Face mFace;
	CFontCache* mCache;
};

