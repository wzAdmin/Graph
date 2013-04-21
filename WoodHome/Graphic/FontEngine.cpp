#include "FontEngine.h"
#include "FontCache.h"
#include <assert.h>
#include "Memory_Check.h"
CFontEngine::CFontEngine(void):mCache(NULL)
{

}

CFontEngine::~CFontEngine(void)
{
	if(mCache)
		Destroy();
}


FontImage CFontEngine::GetFont( unsigned short charCode ,unsigned int width , unsigned int height)
{
	FontImage ftImage = mCache->GetFontImage(charCode,width,height);
	if(!ftImage.pGrayImage)
	{
		FT_Error error = FT_Set_Pixel_Sizes(mFace,width,height);
		assert(0 == error);
		error = FT_Load_Char(mFace,charCode,FT_LOAD_RENDER);
		assert(0 == error);
		ftImage = mCache->AddFontImage(mFace->glyph ,charCode ,width ,height);
	}
	return ftImage;
}

CFontEngine& CFontEngine::Instance()
{
	static CFontEngine engine;
	return engine;
}

void CFontEngine::Destroy()
{
	DELETE_LEAKCHECK(mCache);
	mCache = NULL;
	FT_Error error = FT_Done_Face(mFace);
	assert(0 == error);
	error = FT_Done_FreeType(mFtlib);
	assert(0 == error);
}

bool CFontEngine::Init( const char* fontpath )
{
	FT_Error error = FT_Init_FreeType(&mFtlib);
	assert(0 == error);
	error = FT_New_Face(mFtlib,fontpath,0,&mFace);
	assert(0 == error); 
	mCache = NEW_LEAKCHECK CFontCache(1024,1024);
	return 0==error;
}
