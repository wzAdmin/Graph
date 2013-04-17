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
	std::map<SourceID,CImageBuffer*>::iterator it = mImages.begin();
	for ( ; mImages.end() != it; it++)
	{
		delete it->second;
	}
}

CImageResouceMgr& CImageResouceMgr::Instance()
{
	static CImageResouceMgr mgr;
	return mgr;
}

CImageBuffer* CImageResouceMgr::GetImage( SourceID id )
{
	std::map<SourceID,CImageBuffer*>::iterator it = mImages.find(id);
	if(mImages.end()==it)
	{
		CImageBuffer* p = LoadFormFile(id);
		Add(id,p);
		return p ;
	}
	return it->second;
}

CImageBuffer* CImageResouceMgr::LoadFormFile( SourceID id )
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

void CImageResouceMgr::Add( SourceID id ,CImageBuffer* pImage )
{
	mImages.insert(std::pair<SourceID,CImageBuffer*>(id,pImage));
}
