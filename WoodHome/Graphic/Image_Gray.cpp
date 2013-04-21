#include "ImageBuffer.h"
#include "utils_mem.h"

CGrayImage::CGrayImage(int width ,int height):
mWidth(width),mHeight(height)
{
	mData = (unsigned char*)MALLOC_LEAKCHECK(height*width);
}

CGrayImage::~CGrayImage()
{
	FREE_LEAKCHECK(mData);
}

void CGrayImage::Set(unsigned char* pData,int width,int height,int x,int y)
{
	if(!pData)
		return;
	int beginY = MAX(y,0);
	int endY = MIN(y + height,mHeight);
	int beginX = MAX(x,0);
	int endX = MIN(x + width,mWidth);
	int srcX = ((beginX - x) % width) ;
	int len = width - srcX + 1;
	int destlen = endX - beginX;
	len = MIN(len,destlen);
	int srcY = ((beginY - y) % height) ;
	for (int i = beginY ; i < endY ; i++)
	{
		mem_set<unsigned char>(mData+i*mWidth+beginX,len,pData+srcY*width+srcX,len);
		int leftlen = destlen - len;
		mem_set<unsigned char>(mData+i*mWidth+beginX+len,leftlen,pData+srcY*width,width);
		srcY++;
		if(srcY > height)
			srcY = 0;
	}
	
}