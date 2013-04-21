#pragma once
#include "UItype.h"
#include "resource_image.h"
#include <map>
#include <list>

class CUIFile;
class CImageBuffer;
class UI_API CImageResouceMgr
{
private:
	CImageResouceMgr(void);
	~CImageResouceMgr(void);
public:
	static CImageResouceMgr& Instance();
public:
	CImageBuffer* GetImage(SourceID id);
	void Destroy();
private:
	CImageBuffer* LoadFormFile(SourceID id);
	void Add(SourceID id ,CImageBuffer* pImage);
	void SetCacheSize(int size){mMaxCacheSize = size;}
private:
	std::map<SourceID,CImageBuffer*> mImages;
	std::list<SourceID> mUseLasted;
	int mMaxCacheSize;
	int mCachedSize;
	static const int sDefualtMaxCacheSize = 1024 * 1024 * 4;
};
#define sImageResource CImageResouceMgr::Instance()
