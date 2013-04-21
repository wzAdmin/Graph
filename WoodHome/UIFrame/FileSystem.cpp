#include "FileSystem.h"
#include "UIFile.h"
#include <memory>
#include "Memory_Check.h"

CFileSystem::CFileSystem(void):mFile(NULL),mIndexData(NULL)
{
}


CFileSystem::~CFileSystem(void)
{
	if(mFile)
		Close();
}

void CFileSystem::Open( const char* dataPath )
{
	mFile = NEW_LEAKCHECK CUIFile;
	mFile->Open(dataPath,"rb");
	int Count = 0;
	mFile->Read(&Count,0,4);
	mIndexData = NEW_LEAKCHECK char[Count * 9];
	mFile->Read(mIndexData , 4,Count*9);
}

Sourceitem CFileSystem::GetSource( SourceID id )
{
	Sourceitem item;
	memcpy(&item.offset , mIndexData + 9*(id-1) , 4);
	memcpy(&item.length , mIndexData + 9*(id-1) + 4 , 4);
	item.format = UIFileFormat(mIndexData[9*(id-1) + 8]);
	return item;
}

void CFileSystem::LoadSource( const Sourceitem& item , char* data )
{
	mFile->Read(data,item.offset,item.length);
}

CFileSystem& CFileSystem::Instance()
{
	static CFileSystem fs;
	return fs;
}

void CFileSystem::Close()
{
	if(mFile)
	{
		DELETE_LEAKCHECK(mFile);
		DELETEARR_LEAKCHECK(mIndexData);
		mFile = NULL;
	}
}
