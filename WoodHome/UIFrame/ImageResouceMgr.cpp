#include "ImageResouceMgr.h"
#include "UIFile.h"
#include "ImageBuffer.h"
#include "FileSystem.h"
#include <memory>

CImageResouceMgr::CImageResouceMgr(void)
{
}


CImageResouceMgr::~CImageResouceMgr(void)
{
}

CImageResouceMgr& CImageResouceMgr::Instance()
{
	static CImageResouceMgr mgr;
	return mgr;
}

CImageBuffer* CImageResouceMgr::GetImage( SourceID id )
{
	Sourceitem it = sFilesystem.GetSource(id);
	char* data = new char[it.length];
	sFilesystem.LoadSource(it,data);
	CImageBuffer* pImage = NULL;
	switch (it.format)
	{
	case FM_PNG:
		pImage = new CImage_PNG;
		break;
	case FM_JPG:
		pImage = new CImage_JPG;
		break;
	default:
		return NULL;
	}
	pImage->LoadFromMem(data,it.length);
	delete[] data;
	return pImage;
}
