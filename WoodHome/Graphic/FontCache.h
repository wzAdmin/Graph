#pragma once
#include "GraphicType.h"
#include "Bound.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include HASH_MAP
#include <list>
class CGrayImage;
typedef struct _FontImage
{
	const CGrayImage* pGrayImage;
	CBound bound;
	int advanceX;
	int advanceY;
	int left;
	int top;
}FontImage;
class CFontCache
{
public:
	CFontCache(int cacheWidth, int cacheHeight);
	~CFontCache(void);
public:
	FontImage GetFontImage(unsigned short charCode,int width,int height)const;
	FontImage AddFontImage(const FT_GlyphSlot slot ,unsigned short charCode,int width,int height);
private:
	void Init();
	void DivideBoud(CBound& src,int width,int height);
	FontImage GetBigFont(const FT_GlyphSlot slot);
private:
	std::list<CBound> mAvailableBouds;
	ns_hash::hash_map<unsigned int ,FontImage> mFonts_Cached;
	typedef ns_hash::hash_map<unsigned int,FontImage>::const_iterator CacheIterator;
	typedef std::list<CBound>::iterator BoudIterator;
	CGrayImage*	mCache;
	CGrayImage* mBigFont;
};

