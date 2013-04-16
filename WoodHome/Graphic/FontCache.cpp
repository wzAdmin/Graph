#include "FontCache.h"
#include "ImageBuffer.h"

CFontCache::CFontCache(int cacheWidth, int cacheHeight):mBigFont(NULL)
{
	mCache = new CGrayImage(cacheWidth , cacheHeight);
	Init();
}


CFontCache::~CFontCache(void)
{
	delete mBigFont;
	delete mCache;
}

 FontImage CFontCache::GetFontImage(unsigned short charCode,int width,int height) const
{
	if(width > 255 || height > 255)
	{
		FontImage fi;
		fi.pGrayImage = NULL;
		return fi;
	}
	else
	{
		unsigned int key = (charCode<<16) | (width << 8) | height;
		CacheIterator it = mFonts_Cached.find(key);
		if(mFonts_Cached.end() == it)
		{
			FontImage fi;
			fi.pGrayImage = NULL;
			return fi;
		}
		else
			return it->second;
	}
}

void CFontCache::DivideBoud(CBound& dest,int width,int height )
{
	if(dest.Width()  > dest.Height() )
	{
		CBound left = dest,right = dest;
		left.Right(dest.Left() + width -1);
		left.Top(dest.Top() + height);
		right.Left(dest.Left() + width);
		if(right.Width() && right.Height())
			mAvailableBouds.push_front(right);
		if(left.Width() && left.Height())
			mAvailableBouds.push_front(left);
	}
	else
	{
		CBound top = dest,bottom = dest;
		top.Left(dest.Left() + width);
		top.Bottom(dest.Top() + height -1);
		bottom.Top(dest.Top() + height);
		if(bottom.Width() && bottom.Height())
			mAvailableBouds.push_front(bottom);
		if(top.Width() && top.Height())
			mAvailableBouds.push_front(top);
	}
	dest.Right(dest.Left() + width - 1);
	dest.Bottom(dest.Top() + height - 1);
}

FontImage CFontCache::AddFontImage( const FT_GlyphSlot slot,unsigned short charCode,int width,int height )
{
	if(width > 255 || height>255)
		return GetBigFont(slot);
	BoudIterator it = mAvailableBouds.begin();
	CBound dest;
	for ( ; mAvailableBouds.end() != it; it++)
	{
		if(it->Width() > slot->bitmap.width && it->Height() > slot->bitmap.rows)
		{
			dest = (*it);
			break;
		}
	}
	if(mAvailableBouds.end() == it)
	{
		Init();
		return AddFontImage(slot,charCode,width,height);
	}
	mAvailableBouds.erase(it);
	DivideBoud(dest,slot->bitmap.width,slot->bitmap.rows);
	mCache->Set(slot->bitmap.buffer, slot->bitmap.width , slot->bitmap.rows, dest.Left(), dest.Top());
	FontImage ftImage;
	ftImage.advanceX = slot->advance.x>>6;
	ftImage.advanceY = slot->advance.y>>6;
	ftImage.boud = dest;
	ftImage.left = slot->bitmap_left;
	ftImage.top  = slot->bitmap_top;
	ftImage.pGrayImage = mCache;
	unsigned int key = (charCode<<16) | (width << 8) | height;
	mFonts_Cached.insert(std::pair<unsigned int,FontImage>(key,ftImage));
	return ftImage;
}

void CFontCache::Init()
{
	mAvailableBouds.clear();
	mFonts_Cached.clear();
	CBound allBound(0, mCache->Width()-1 ,0 , mCache->Height()-1);
	mAvailableBouds.push_back(allBound);
}

FontImage CFontCache::GetBigFont( const FT_GlyphSlot slot)
{
	if(mBigFont && mBigFont->Height() >= slot->bitmap.rows && mBigFont->Width() > slot->bitmap.width)
		mBigFont->Set(slot->bitmap.buffer, slot->bitmap.width , slot->bitmap.rows, 0, 0);
	else
	{
		if(mBigFont)
			delete mBigFont;
		mBigFont = new CGrayImage(slot->bitmap.width,slot->bitmap.rows);
		mBigFont->Set(slot->bitmap.buffer, slot->bitmap.width , slot->bitmap.rows, 0, 0);
	}
	FontImage ftImage;
	ftImage.advanceX = slot->advance.x>>6;
	ftImage.advanceY = slot->advance.y>>6;
	ftImage.boud = CBound(0 ,slot->bitmap.width-1 ,0 ,slot->bitmap.rows-1);
	ftImage.left = slot->bitmap_left;
	ftImage.top  = slot->bitmap_top;
	ftImage.pGrayImage = mBigFont;
	return ftImage;
}
