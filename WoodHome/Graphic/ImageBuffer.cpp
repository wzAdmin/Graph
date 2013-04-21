#include "ImageBuffer.h"
#include "utils_mem.h"
#include <stdlib.h>

CImageBuffer::CImageBuffer(void):
mData(NULL),
mAlpha(NULL),
mWidth(0),
mHeight(0)
{
}

CImageBuffer::~CImageBuffer(void)
{
	FREE_LEAKCHECK(mData);
	FREE_LEAKCHECK(mAlpha);
}

void CImageBuffer::Initialize( int width , int height, bool hasAlpha )
{
	mWidth = width;
	mHeight = height;
	mData = (unsigned short*)MALLOC_LEAKCHECK(Stride()*height*sizeof(unsigned short));
	if(hasAlpha)
		mAlpha = (unsigned char*)MALLOC_LEAKCHECK(width*height);
}

void CImageBuffer::ClearColor( COLORARGB color )
{
	unsigned short color565 = RGB888ToRGB565(color);
	mem_set(mData,Stride()*mHeight,&color565,1);
}

void CImageBuffer::Load( const char* path )
{
	FILE* hFile = fopen(path,"rb");
	fseek(hFile , 0 , SEEK_END);
	int length = ftell(hFile);
	char* data = (char*)MALLOC_LEAKCHECK(length);
	fseek(hFile , 0 , SEEK_SET);
	int ZI = fread(data,1,length,hFile);
	fclose(hFile);
	LoadFromMem(data,length);
	FREE_LEAKCHECK(data);
}

int CImageBuffer::GetSize()
{
	if(mAlpha)
		return mHeight * mWidth + mHeight * Stride() * 2;
	else
		return mHeight * Stride() * 2;
}
