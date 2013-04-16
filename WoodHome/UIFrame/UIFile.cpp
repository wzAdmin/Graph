#include "UIFile.h"
#include <assert.h>

CUIFile::CUIFile(void):mFile(NULL)
{
}

CUIFile::CUIFile( const char* path ,const char* mode)
{
	Open(path,mode);
}


CUIFile::~CUIFile(void)
{
	Close();
}

void CUIFile::Read( void* pData , int offset , int length )
{
	assert(mFile);
	fseek(mFile,offset,SEEK_SET);
	int len = fread(pData ,1,length,mFile);
	assert(len == length);
}

void CUIFile::Close()
{
	if(mFile)
		fclose(mFile);
	mFile = NULL;
}

bool CUIFile::Open( const char* path,const char* mode)
{
	mFile = fopen(path,mode);
	return NULL != mFile;
}

int CUIFile::Length()
{
	if(!mFile)
		return 0;
	long curpos, length;
	curpos = ftell(mFile);
	fseek(mFile, 0L, SEEK_END);
	length = ftell(mFile);
	fseek(mFile, curpos, SEEK_SET);
	return length;
}
