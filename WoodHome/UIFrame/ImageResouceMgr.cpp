#include "ImageResouceMgr.h"
#include "UIFile.h"
#include "ImageBuffer.h"
#include "FileSystem.h"
#include <memory>

CImageResouceMgr::CImageResouceMgr(void):mCachedSize(0),mMaxCacheSize(sDefualtMaxCacheSize)
{
}


CImageResouceMgr::~CImageResouceMgr(void)
{
	Destroy();
}

CImageResouceMgr& CImageResouceMgr::Instance()
{
	static CImageResouceMgr mgr;
	return mgr;
}

CImageBuffer* CImageResouceMgr::GetImage( SourceID id )
{
	std::map<SourceID,CImageBuffer*>::iterator it = mImages.find(id);
	CImageBuffer* p = NULL;
	if(mImages.end()==it)
	{
		p = LoadFormFile(id);
		Add(id,p);
	}
	else
	{
		p =  it->second;
		std::list<SourceID>::iterator lsit= mUseLasted.begin();
		for ( ; mUseLasted.end() != lsit ; lsit++)
		{
			if(id == *lsit)
			{
				mUseLasted.erase(lsit);
				mUseLasted.push_front(id);
				break;
			}
		}
	}
	return p;
}

CImageBuffer* CImageResouceMgr::LoadFormFile( SourceID id )
{
	Sourceitem it = sFilesystem.GetSource(id);
	char* data = NEW_LEAKCHECK char[it.length];
	sFilesystem.LoadSource(it,data);
	CImageBuffer* pImage = NULL;
	switch (it.format)
	{
	case FM_PNG:
		pImage = NEW_LEAKCHECK CImage_PNG;
		break;
	case FM_JPG:
		pImage = NEW_LEAKCHECK CImage_JPG;
		break;
	default:
		return NULL;
	}
	pImage->LoadFromMem(data,it.length);
	DELETEARR_LEAKCHECK(data);
	return pImage;
}

void CImageResouceMgr::Add( SourceID id ,CImageBuffer* pImage )
{
	mImages.insert(std::pair<SourceID,CImageBuffer*>(id,pImage));
	while(mCachedSize > mMaxCacheSize)
	{
		std::map<SourceID,CImageBuffer*>::iterator it = mImages.find(mUseLasted.back());
		mCachedSize -= it->second->GetSize();
		DELETE_LEAKCHECK(it->second);
		mUseLasted.pop_back();
		mImages.erase(it);
	}
	mCachedSize += pImage->GetSize();
	mUseLasted.push_front(id);
}

void CImageResouceMgr::Destroy()
{
	std::map<SourceID,CImageBuffer*>::iterator it = mImages.begin();
	for ( ; mImages.end() != it; it++)
	{
		DELETE_LEAKCHECK(it->second);
	}
	mImages.clear();
}
