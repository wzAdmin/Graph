#include "ImageBuffer.h"
#include "Graphics.h"
#include "utils_mem.h"
#include "GraphicType.h"
#include "Transfrom.h"
#include "utils.h"
void CGraphics::DrawGrayImage(const CGrayImage* pImage,const CBound& srcBound , const CBound& destBound,COLORARGB color)
{
	if(!pImage)
		return;
	unsigned short color565 = RGB888ToRGB565(color);
	unsigned int srcColor = ((color565 <<16) | color565 ) & 0x07E0F81F; 
	const unsigned char* data = pImage->GetPixels();
	int ImageWidth = pImage->Width();
	int ImageHeight = pImage->Height();
	CBound src(0,ImageWidth-1,0,ImageHeight-1);
	if(!CBound::Intersect(srcBound,src,src) || !data)
		return;
	int beginY = MAX(destBound.Top(),0);
	int endY = MIN(destBound.Bottom() + 1,mHeight);
	int beginX = MAX(destBound.Left(),0);
	int endX = MIN(destBound.Right() + 1,mWidth);
	int srcWidth = src.Width();
	int srcHeight= src.Height();
	int srcX = ((beginX - destBound.Left()) % srcWidth) + src.Left();
	int srcY = ((beginY - destBound.Top()) % srcHeight) + src.Top();

	for (int i = beginY ; i < endY  ; i++)
	{
		srcX = ((beginX - destBound.Left()) % srcWidth) + src.Left();
		for (int j = beginX ; j < endX ; j++)
		{
			Alpha(mpFrambuffer[i*mWidth+j],color565,data[srcY*ImageWidth+srcX]>>3);
			srcX++;
			if(srcX > src.Right())
				srcX = src.Left();
		}
		srcY++;
		if(srcY > src.Bottom())
			srcY = src.Top();
	}
	
}
void CGraphics::DrawImage_Repeat(const CImageBuffer* pImage , const CBound& srcBound , const CBound& destBound)
{
	if(!pImage)
		return;
	const unsigned short* data = pImage->GetPixels();
	const unsigned char* alpha = pImage->GetAlpha();
	int ImageWidth = pImage->Width();
	int ImageHeight = pImage->Height();
	CBound src(0,ImageWidth-1,0,ImageHeight-1);
	if(!CBound::Intersect(srcBound,src,src) || !data)
		return;
	int beginY = MAX(destBound.Top(),0);
	int endY = MIN(destBound.Bottom() + 1,mHeight);
	int beginX = MAX(destBound.Left(),0);
	int endX = MIN(destBound.Right() + 1,mWidth);
	int srcWidth = src.Width();
	int srcHeight= src.Height();
	int srcX = ((beginX - destBound.Left()) % srcWidth) + src.Left();
	int len = src.Right() - srcX + 1;
	int destlen = endX - beginX;
	len = MIN(len,destlen);
	int srcY = ((beginY - destBound.Top()) % srcHeight) + src.Top();
	if(!alpha)
	{
		for (int i = beginY ; i < endY ; i++)
		{
			mem_set<unsigned short>(mpFrambuffer+i*mWidth+beginX,len,data+srcY*ImageWidth+srcX,len);
			int leftlen = destlen - len;
			mem_set<unsigned short>(mpFrambuffer+i*mWidth+beginX+len,leftlen,data+srcY*ImageWidth+src.Left(),srcWidth);
			srcY++;
			if(srcY > src.Bottom())
				srcY = src.Top();
		}
	}
	else
	{
		for (int i = beginY ; i < endY ; i++)
		{
			srcX = ((beginX - destBound.Left()) % srcWidth) + src.Left();
			for (int j = beginX ; j < endX ; j++)
			{
				Alpha(mpFrambuffer[i*mWidth+j],data[srcY*ImageWidth+srcX],alpha[srcY*ImageWidth+srcX]);
				srcX++;
				if(srcX > src.Right())
					srcX = src.Left();
			}
			srcY++;
			if(srcY > src.Bottom())
				srcY = src.Top();
		}
	}
}


void CGraphics::DrawImage_Scale(const CImageBuffer* pImage , const CBound& srcBound , const CBound& destBound)
{
	if(!pImage)
		return;
	const unsigned short* data = pImage->GetPixels();
	const unsigned char* alpha = pImage->GetAlpha();
	int ImageWidth = pImage->Width();
	int ImageHeight = pImage->Height();
	CBound src(0,ImageWidth-1,0,ImageHeight-1);
	if(!CBound::Intersect(srcBound,src,src) || !data)
		return;
	if(src.Width() == destBound.Width() && src.Height() == destBound.Height())
		return DrawImage_Repeat(pImage,src,destBound);
	int beginY = MAX(destBound.Top(),0);
	int endY = MIN(destBound.Bottom() + 1,mHeight);
	int beginX = MAX(destBound.Left(),0);
	int endX = MIN(destBound.Right() + 1,mWidth);
	int destWidth = destBound.Width() ;
	int destHeight= destBound.Height() ;
	int srcWidth = src.Width();
	int srcHeight= src.Height();
	int stride = Stride();

	unsigned short* psrcX = (unsigned short*)malloc(sizeof(unsigned short)*(endX-beginX)*2);
	int tempX = endX;
	for (int i = beginX ; i < endX ; i++)
	{
		psrcX[(i-beginX)*2]=(unsigned short)((i - destBound.Left())*srcWidth/destWidth) + srcBound.Left();
		psrcX[(i-beginX)*2+1]=(unsigned short)(((i - destBound.Left())*srcWidth - destWidth*psrcX[(i-beginX)*2])*32/destWidth);
		if (srcWidth-1 == psrcX[(i-beginX)*2] && i < tempX)
		{
			tempX = i;
		}
	}
	unsigned short* psrcY = (unsigned short*)malloc(sizeof(unsigned short)*(endY - beginY)*2);
	int tempY = endY;
	for (int i = beginY ; i < endY ; i++)
	{
		psrcY[(i-beginY)*2]=(unsigned short)((i - destBound.Top())*srcHeight/destHeight) + srcBound.Top();
		psrcY[(i-beginY)*2+1]=(unsigned short)(((i - destBound.Top())*srcHeight - destHeight*psrcY[(i-beginY)*2])*32/destHeight);
		if (srcHeight-1 == psrcY[(i-beginY)*2] && i < tempY)
		{
			tempY = i;
		}
	}
	if(alpha)
	{
		for (int i = beginY ; i < tempY ; i++)
		{
			int srcY = psrcY[(i-beginY)*2];
			int alphaY = psrcY[(i-beginY)*2+1];
			for (int j = beginX ; j < tempX ; j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				unsigned short c1 = data[srcY*ImageWidth+srcX];
				unsigned short c2 = data[srcY*ImageWidth+srcX+1];
				unsigned short c3 = data[(srcY+1)*ImageWidth+srcX];
				unsigned short c4 = data[(srcY+1)*ImageWidth+srcX+1];
				unsigned char a1 = alpha[srcY*ImageWidth+srcX];
				unsigned char a2 = alpha[srcY*ImageWidth+srcX+1];
				unsigned char a3 = alpha[(srcY+1)*ImageWidth+srcX];
				unsigned char a4 = alpha[(srcY+1)*ImageWidth+srcX+1];
 				Alpha(c1,c2,alphaX);
				Alpha(c3,c4,alphaX);
 				Alpha(c1,c3,alphaY);
				Alpha(a1,a2,alphaX);
				Alpha(a3,a4,alphaX);
				Alpha(a1,a3,alphaY);
				Alpha(mpFrambuffer[i*stride+j],c1,a1);
			}
			for (int j = tempX ; j < endX ;j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				unsigned short c1 = data[srcY*ImageWidth+srcX];
				unsigned short c3 = data[(srcY+1)*ImageWidth+srcX];
				Alpha(c1,c3,alphaY);
				unsigned char a1 = alpha[srcY*ImageWidth+srcX];
				unsigned char a3 = alpha[(srcY+1)*ImageWidth+srcX];
				Alpha(a1,a3,alphaY);
				Alpha(mpFrambuffer[i*stride+j],c1,a1);
			}
		}
		for (int i = tempY ; i < endY ; i++)
		{
			int srcY = psrcY[(i-beginY)*2];
			int alphaY = psrcY[(i-beginY)*2+1];
			for (int j = beginX ; j < tempX ; j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				unsigned short c1 = data[srcY*ImageWidth+srcX];
				unsigned short c2 = data[srcY*ImageWidth+srcX+1];
				Alpha(c1,c2,alphaX);
				unsigned char a1 = alpha[srcY*ImageWidth+srcX];
				unsigned char a2 = alpha[srcY*ImageWidth+srcX+1];
				Alpha(a1,a2,alphaX);
				Alpha(mpFrambuffer[i*stride+j],c1,a1);
			}
			for (int j = tempX ; j < endX ;j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				Alpha(mpFrambuffer[i*stride+j] ,data[srcY*ImageWidth+srcX],alpha[srcY*ImageWidth+srcX]);
			}
		}
	}
	else
	{
		for (int i = beginY ; i < tempY ; i++)
		{
			int srcY = psrcY[(i-beginY)*2];
			int alphaY = psrcY[(i-beginY)*2+1];
			for (int j = beginX ; j < tempX ; j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				unsigned short c1 = data[srcY*ImageWidth+srcX];
				unsigned short c2 = data[srcY*ImageWidth+srcX+1];
				unsigned short c3 = data[(srcY+1)*ImageWidth+srcX];
				unsigned short c4 = data[(srcY+1)*ImageWidth+srcX+1];
				Alpha(c1,c2,alphaX);
				Alpha(c3,c4,alphaX);
				Alpha(c1,c3,alphaY);
				mpFrambuffer[i*stride+j]=c1;
			}
			for (int j = tempX ; j < endX ;j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				unsigned short c1 = data[srcY*ImageWidth+srcX];
				unsigned short c3 = data[(srcY+1)*ImageWidth+srcX];
				Alpha(c1,c3,alphaY);
				mpFrambuffer[i*stride+j]=c1;
			}
		}
		for (int i = tempY ; i < endY ; i++)
		{
			int srcY = psrcY[(i-beginY)*2];
			int alphaY = psrcY[(i-beginY)*2+1];
			for (int j = beginX ; j < tempX ; j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				unsigned short c1 = data[srcY*ImageWidth+srcX];
				unsigned short c2 = data[srcY*ImageWidth+srcX+1];
				Alpha(c1,c2,alphaX);
				mpFrambuffer[i*stride+j]=c1;
			}
			for (int j = tempX ; j < endX ;j++)
			{
				int srcX = psrcX[(j-beginX)*2];
				int alphaX = psrcX[(j-beginX)*2+1];
				mpFrambuffer[i*stride+j] = data[srcY*ImageWidth+srcX];
			}
		}
	}
	free(psrcX);
	free(psrcY);
}

void CGraphics::DrawImage( const CImageBuffer* pImage ,const CTransfrom& tf ,const CBound* srcBound /*= NULL*/, const CBound* clipBuond /*= NULL*/ )
{
	if(!pImage)
		return;
	const unsigned short* pData = pImage->GetPixels();
	int iamgeWidth = pImage->Width();
	int imageHeight = pImage->Height();
	CBound src(0,pImage->Width() - 1, 0 ,pImage->Height() -1 );
	if(srcBound)
	{
		if(!CBound::Intersect(src,*srcBound,src))
			return;
	}
	src.Bottom(src.Bottom() + 2);
	src.Right(src.Right() + 2);
	src.Left(src.Left() - 2);
	src.Top(src.Top() - 2);
	CBound dest = tf.Transform(src);

 	src.Bottom(src.Bottom() - 3);
 	src.Right(src.Right() - 3);
 	src.Left(src.Left() + 2);
 	src.Top(src.Top() + 2);
	if(clipBuond)
		CBound::Intersect(dest,*clipBuond,dest);
	CBound org = src;
	org.Bottom(src.Bottom() + 1);
	org.Right(src.Right() + 1);
	org.Left(src.Left() - 1);
	org.Top(src.Top() - 1);
	if(CBound::Intersect(dest,CBound(0,mWidth - 1 , 0 ,mHeight -1),dest))
	{
		const matrixf<3>& mt = tf.Inverse();
		int stride = Stride();
		for (int i = dest.Top() ; i <= dest.Bottom()  ; i++)
		{
			for (int j = dest.Left() ;j <= dest.Right()  ;j++ )
			{
				double fi = double(i);
				double fj = double(j);
				double fx=mt[0][0]*fj + mt[1][0]*fi + mt[2][0];
				double fy=mt[0][1]*fj + mt[1][1]*fi + mt[2][1];
				int srcX = Double2Int(fx-0.4999999);
				int srcY = Double2Int(fy-0.4999999);

  				if(org.Contain(srcX , srcY))
  				{
					char alphax = char(Double2Int(32 * (fx - srcX)));
					char alphay = char(Double2Int(32 * (fy - srcY)));
					if(src.Contain(srcX,srcY))
					{
						unsigned short c1 = pData[srcX + srcY * iamgeWidth];
						unsigned short c2 = pData[srcX + 1 + srcY * iamgeWidth];
						unsigned short c3 = pData[srcX + (srcY  + 1)* iamgeWidth];
						unsigned short c4 = pData[srcX + 1 + (srcY + 1) * iamgeWidth];
						Alpha(c1,c2,alphax);
						Alpha(c3,c4,alphax);
						Alpha(c1,c3,alphay);
						mpFrambuffer[i* stride + j] = c1;
					}
  					else if(srcX==src.Left() - 1 && srcY == src.Top() - 1)
  						Alpha(mpFrambuffer[i* stride + j],pData[srcX + 1 + (srcY + 1) * iamgeWidth],alphax);
  					else if(srcY == src.Top() - 1)
  						Alpha(mpFrambuffer[i* stride + j],pData[srcX + (1 + srcY) * iamgeWidth],alphay);
  					else if(srcX==src.Left() - 1)
  						Alpha(mpFrambuffer[i* stride + j],pData[srcX + 1 + srcY * iamgeWidth],alphax);
  					else if(srcX==src.Right() + 1 )
  						Alpha(mpFrambuffer[i* stride + j],pData[srcX + srcY * iamgeWidth],32 - alphax);
  					else if(srcY==src.Bottom() + 1)
  						Alpha(mpFrambuffer[i* stride + j],pData[srcX + srcY * iamgeWidth],32 - alphay);
  				}
			}
		}

	}
}

void CGraphics::DrawImage( const CGrayImage* pImage ,const CTransfrom& tf ,COLORARGB color,const CBound* srcBound /*= NULL*/,const CBound* clipBuond /*= NULL*/ )
{
	if(!pImage)
		return;
	const unsigned char* pData = pImage->GetPixels();
	int iamgeWidth = pImage->Width();
	int imageHeight = pImage->Height();
	CBound src(0,pImage->Width() - 1, 0 ,pImage->Height() -1 );
	if(srcBound)
	{
		if(!CBound::Intersect(src,*srcBound,src))
			return;
	}
	unsigned short color565  = RGB888ToRGB565(color);
	src.Bottom(src.Bottom() + 2);
	src.Right(src.Right() + 2);
	src.Left(src.Left() - 2);
	src.Top(src.Top() - 2);
	CBound dest = tf.Transform(src);
	src.Bottom(src.Bottom() - 3);
	src.Right(src.Right() - 3);
	src.Left(src.Left() + 2);
	src.Top(src.Top() + 2);
	if(clipBuond)
		CBound::Intersect(dest,*clipBuond,dest);
	CBound org = src;
	org.Bottom(src.Bottom() + 1);
	org.Right(src.Right() + 1);
	org.Left(src.Left() - 1);
	org.Top(src.Top() - 1);
	if(CBound::Intersect(dest,CBound(0,mWidth - 1 , 0 ,mHeight -1),dest))
	{
		const matrixf<3>& mt = tf.Inverse();
		int stride = Stride();
		for (int i = dest.Top() ; i <= dest.Bottom()  ; i++)
		{
			for (int j = dest.Left() ;j <= dest.Right()  ;j++ )
			{
				double fi = double(i);
				double fj = double(j);
				double fx=mt[0][0]*fj + mt[1][0]*fi + mt[2][0];
				double fy=mt[0][1]*fj + mt[1][1]*fi + mt[2][1];
				int srcX = Double2Int(fx-0.4999999);
				int srcY = Double2Int(fy-0.4999999);
				if(org.Contain(srcX , srcY))
				{
					char alphax = char(Double2Int(32 * (fx - srcX)));
					char alphay = char(Double2Int(32 * (fy - srcY)));
					if(src.Contain(srcX,srcY))
					{
						unsigned char c1 = pData[srcX + srcY * iamgeWidth];
						unsigned char c2 = pData[srcX + 1 + srcY * iamgeWidth];
						unsigned char c3 = pData[srcX + (srcY  + 1)* iamgeWidth];
						unsigned char c4 = pData[srcX + 1 + (srcY + 1) * iamgeWidth];
						Alpha(c1,c2,alphax);
						Alpha(c3,c4,alphax);
						Alpha(c1,c3,alphay);
						Alpha(mpFrambuffer[i* stride + j],color565,c1>>3);
					}
 					else if(srcX==src.Left() - 1 && srcY == src.Top() - 1)
 					{
 						alphax = ((pData[srcX + 1 + (srcY + 1) * iamgeWidth]>>3) * alphax)>>5;
 						Alpha(mpFrambuffer[i* stride + j],color565,alphax);
 					}
 					else if(srcY == src.Top() - 1)
 					{
 						alphay = ((pData[srcX + (srcY + 1) * iamgeWidth]>>3) * alphay)>>5;
 						Alpha(mpFrambuffer[i* stride + j],color565,alphay);
 					}
 					else if(srcX==src.Left() - 1)
 					{
 						alphax = ((pData[srcX + 1 +  srcY * iamgeWidth]>>3) * alphax)>>5;
 						Alpha(mpFrambuffer[i* stride + j],color565,alphax);
 					}
 					else if(srcX==src.Right() + 1 )
 					{
 						alphax = ((pData[srcX +  srcY * iamgeWidth]>>3) * (32 - alphax))>>5;
 						Alpha(mpFrambuffer[i* stride + j],color565, alphax);
 					}
 					else if(srcY==src.Bottom() + 1)
 					{
 						alphay = ((pData[srcX +  srcY * iamgeWidth]>>3) * (32-alphay))>>5;
 						Alpha(mpFrambuffer[i* stride + j],color565,alphay);
 					}
				}
			}
		}

	}
}