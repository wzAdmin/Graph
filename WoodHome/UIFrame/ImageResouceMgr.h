#pragma once
#include "UItype.h"
#include "resource_image.h"

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
};
#define sImageResource CImageResouceMgr::Instance()
