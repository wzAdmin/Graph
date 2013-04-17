#pragma once
#include "UItype.h"
#include "resource_image.h"
#include <map>

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
private:
	CImageBuffer* LoadFormFile(SourceID id);
	void Add(SourceID id ,CImageBuffer* pImage);
private:
	std::map<SourceID,CImageBuffer*> mImages;
};
#define sImageResource CImageResouceMgr::Instance()
