#include "Graphics.h"
#include "ImageBuffer.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include "utils.h"

#include "Memory_Check.h"
CGraphics::CGraphics(  CImageBuffer* image )
{
	Initialize(image);
}


CGraphics::~CGraphics(void)
{
	delete mClip;
}

void CGraphics::Initialize(  CImageBuffer* image)
{
	mWidth = image->Width();
	mHeight = image->Height();
	mClip = new CClipUtils(0 , 0 , mWidth - 1, mHeight - 1);
	mpFrambuffer = const_cast<unsigned short*>(image->GetPixels());
	mImagebuffer = image;
}

void CGraphics::DrawCirce( CPosition center , int R ,COLORARGB color )
{
	unsigned short Color = RGB888ToRGB565(color);
	int left = center.X() - R -2;
	int right = center.X() + R + 2;
	int top = center.Y() - R - 2;
	int bottom = center.Y() + R + 2;
	left = left < 0 ? 0 : left;
	right = right > mWidth  ? mWidth  : right + 1;
	top = top < 0 ? 0 : top;
	bottom = bottom > mHeight ? mHeight : bottom + 1;
	int stride = Stride();
	int dis = (top - center.Y()) * (top - center.Y()) + (left - center.X()) * (left - center.X()) - R * R;
	for (int height = top ; height < bottom  ; height++)
	{
		int tempDis = dis;
		for (int width = left ; width < right ; width++)
		{
			if(tempDis + R < 0)
				mpFrambuffer[height*stride + width] = Color;
			else if(tempDis - R < 0)
			{
				int a = 16 - ((tempDis * 16)/R);
				Alpha(mpFrambuffer[height*stride + width],Color,char(a));
			}
			tempDis +=  (width<<1) + 1 - (center.X()<<1);
		}
		dis += (height<<1) + 1 - (center.Y()<<1);
	}
}

void CGraphics::Line( CPosition A , CPosition B ,int Width ,COLORARGB color )
{
	if(!mClip->ClipLine(A , B))
		return;
	DrawCirce(A,Width/2,color);
	DrawCirce(B,Width/2,color);
	unsigned short Color = RGB888ToRGB565(color);
	int left = 0;
	int right = mWidth;
	int top = 0;
	int bottom = mHeight;
	double AB = (A.X() - B.X()) * (A.X() - B.X()) + (A.Y() - B.Y()) * (A.Y() - B.Y()) ;
	AB = sqrt(AB);
	double SArea = AB * Width / 2;
	int stride = Stride();
	for (int height = top ; height < bottom  ; height++)
	{
		for (int width = left ; width < right ; width++)
		{
			int S = (A.X() - width) * (B.Y() - height) - (B.X() - width)*(A.Y() - height);
			if(S < 0)
				S=-S;
			if(int64((width - A.X()) * (A.X() - B.X()) - (height - A.Y())* (B.Y() - A.Y()) )*
			((width - B.X()) * (A.X() - B.X())  -(height - B.Y())* (B.Y() - A.Y()) ) < 0)
			{
				int a = int(16 - (S - SArea)*16/AB);
				if(a > 32)
					mpFrambuffer[(height)*stride + width] = Color;
				else if(a > 0)
					Alpha(mpFrambuffer[(height)*stride + width],Color,char(a));
			}
		}
	}
}

void CGraphics::LineDDA( CPosition A , CPosition B ,int width ,COLORARGB color )
{
	if(!mClip->ClipLine(A , B))
		return;
	DrawCirce(A,width/2,color);
	DrawCirce(B,width/2,color);
	unsigned short Color = RGB888ToRGB565(color);
	unsigned int Color565 = Color;
	Color565 = ((Color565 <<16) | Color565 ) & 0x07E0F81F;
	int stride = Stride();
	int ky = stride;
	int kx = 1;
	int maxX = mWidth;
	int maxY = mHeight;
	if(ABS(A.X() - B.X()) < ABS(A.Y() - B.Y()))
	{
		A.TransposeXY();
		B.TransposeXY();
		kx = stride;
		ky = 1;
		maxX = mHeight;
		maxY = mWidth;
	}
	if(A.X() > B.X())
		CPosition::Swap(A,B);
	int a = B.Y() - A.Y();
	int b = A.X() - B.X();
	int c = A.Y()*B.X() - A.X()*B.Y();
	int beginX = int(width * sqrt(a * a /( b * b + float(a * a)))/2 + 1);
	int endX = B.X() + beginX;
	beginX = A.X() - beginX;
	int r = int(width * sqrt(1.0f + float(a * a) / (b * b)))/2 + 2;
	double AB = double((A.X() - B.X()) * (A.X() - B.X()) + (A.Y() - B.Y()) * (A.Y() - B.Y())) ;
	AB = sqrt(AB);
	double SArea = AB * width / 2;
	int b2 = a*A.Y() - b*A.X();
	int b3 = a*B.Y() - b*B.X();
	int c1 = A.X() * B.Y() - B.X() * A.Y();
	beginX = beginX < 0 ? 0 : beginX;
	endX = endX > maxX ? maxX : endX + 1;
	int y = 0;
	if((-c-a*beginX)*b > 0)
		y = int(float(-c-a*beginX)/b + 0.5);
	else
		y = int(float(-c-a*beginX)/b - 0.5);
	int dlta = 2*(a*beginX + b*y + c) + 1;
	for (int x = beginX ; x < endX ; x++)
	{
		int beginY = y - r;
		beginY = beginY < 0?0:beginY;
		int endY = y + r;
		endY = endY > maxY ? maxY:endY + 1;
		for(int yy = beginY   ; yy < endY  ;yy++)
		{
			int S = c1 - b*yy - a*x;
			S=S<0?-S:S;
			int S1 = x * b - yy * a;
			int t1 = S1 + b2;
			int t2 = S1 + b3;
			if((t1^t2) < 0)
			{
				if(S - SArea + AB < 0)
					mpFrambuffer[yy * ky + x*kx] = Color;
 				else if(S - SArea - AB < 0)
 				{
 					int a = int(16 - (S - SArea)*16/AB);
 					Alpha(mpFrambuffer[yy * ky + x*kx ],Color565,char(a));
 				}
			}
		}
		dlta += a * 2;
		if(a > 0 && dlta > 0)
		{
			y++;
			dlta+=b * 2;
		}
		else if(dlta < 0 && a < 0)
		{
			y--;
			dlta-=b * 2;
		}
	}
}

void CGraphics::LineDDA( CPosition A ,int width1 ,CPosition B , int width2,COLORARGB color )
{
	if(!mClip->ClipLine(A , B))
		return;
	DrawCirce(A,width1/2,color);
	DrawCirce(B,width2/2,color);
	unsigned short Color = RGB888ToRGB565(color);
	unsigned int Color565 = Color;
	Color565 = ((Color565 <<16) | Color565 ) & 0x07E0F81F;
	int stride = Stride();
	int ky = stride;
	int kx = 1;
	int maxX = mWidth;
	int maxY = mHeight;
	if(ABS(A.X() - B.X()) < ABS(A.Y() - B.Y()))
	{
		A.TransposeXY();
		B.TransposeXY();
		kx = stride;
		ky = 1;
		maxX = mHeight;
		maxY = mWidth;
	}
	if(A.X() > B.X())
	{
		width1 ^= width2;
		width2 ^= width1;
		width1 ^= width2;
		CPosition::Swap(A,B);
	}

	int deltaW = width1 - width2;
	int width = width1;
	CPosition Maxpos = A;
	if(deltaW < 0)
	{
		width = width2;
		Maxpos = B;
		deltaW =-deltaW;
	}
	int a = B.Y() - A.Y();
	int b = A.X() - B.X();
	int c = A.Y()*B.X() - A.X()*B.Y();
	int beginX = int(width * sqrt(a * a /( b * b + float(a * a)))/2 + 1);
	int endX = B.X() + beginX;
	beginX = A.X() - beginX;
	int r = int((width + 2) * sqrt(1.0f + float(a * a) / (b * b)))/2 + 2;
	double AB = (A.X() - B.X()) * (A.X() - B.X()) + (A.Y() - B.Y()) * (A.Y() - B.Y()) ;
	AB = sqrt(AB);
	double SArea = AB * width / 2;
	double a1 = AB*AB*width;
	double a2 = 2*AB;
	double a3 = (a2*AB);
	int b1 = a*Maxpos.Y() - b*Maxpos.X();
	int b2 = a*A.Y() - b*A.X();
	int b3 = a*B.Y() - b*B.X();
	beginX = beginX < 0 ? 0 : beginX;
	endX = endX > maxX ? maxX : endX + 1;
	int y = 0;
	if((-c-a*beginX)*b > 0)
		y = int(float(-c-a*beginX)/b + 0.5);
	else
		y = int(float(-c-a*beginX)/b - 0.5);
	int dlta = 2*(a*beginX + b*y + c) + 1;
	int temp = kx*beginX;
	for (int x = beginX ; x < endX ; x++)
	{		
		int beginY = y - r;
		beginY = beginY < 0?0:beginY;
		int endY = y +r;
		endY = endY > maxY ? maxY:endY + 1;
		for(int yy = beginY   ; yy < endY ;yy++)
		{
			int S = (A.X() - x) * (B.Y() - yy) - (B.X() - x)*(A.Y() - yy);
			S = S>0?S:-S;
			int S1 = x * b - yy * a;
			int t1 = S1 + b2;
			int t2 = S1 + b3;
			S1+=b1;
			S1 = S1>0?S1:-S1;
			if((t1^t2)<0)
			{
				double a = (deltaW * S1 + a2 * S -a1 );
				if(a + a3 < 0)
					mpFrambuffer[temp + yy * ky] = Color;
				else if(a - a3 < 0)
				{
					a = 16 - 16 * a / a3;
					Alpha(mpFrambuffer[temp + yy * ky ],Color565,char(a));
				}
			}
		}
		temp+=kx;
		dlta += a * 2;
		if(a > 0 && dlta > 0)
		{
			y++;
			dlta+=b * 2;
		}
   		else if(dlta < 0 && a < 0)
   		{
   			y--;
   			dlta-=b * 2;
   		}
	}
}

void CGraphics::LineDDA( CPosition A , CPosition B ,COLORARGB color )
{
	if(!mClip->ClipLine(A , B))
		return;
	unsigned short Color = RGB888ToRGB565(color);
	int stride = Stride();
	int ky = stride;
	int kx = 1;
	int maxX = mWidth;
	int maxY = mHeight;
	if(ABS(A.X() - B.X()) < ABS(A.Y() - B.Y()))
	{
		A.TransposeXY();
		B.TransposeXY();
		kx = stride;
		ky = 1;
		maxX = mHeight;
		maxY = mWidth;
	}
	if(A.X() > B.X())
		CPosition::Swap(A,B);
	int a = B.Y() - A.Y();
	int b = A.X() - B.X();
	int left = A.X() < 0 ? 0 : A.X();
	int right = B.X() > maxX ? maxX : B.X() + 1;
	int top = A.Y() < 0 ? 0 : A.Y();
	int bottom = B.Y() > maxY ? maxY : B.Y() + 1;
	int dlta = 1;
	int y = top;
	for (int x = left ; x < right ; x++)
	{
		mpFrambuffer[y * ky + x * kx] = Color;
		dlta += a * 2;
		if(a > 0 && dlta > 0)
		{
			y++;
			dlta+=b * 2;
		}
		else if(dlta < 0 && a < 0)
		{
			y--;
			dlta-=b * 2;
		}
	}
}



void CGraphics::DrawBound( const CBound& bound , COLORARGB color )
{
	LineDDA(CPosition(bound.Left(),bound.Top()),CPosition(bound.Right(),bound.Top()),color);
	LineDDA(CPosition(bound.Left(),bound.Top()),CPosition(bound.Left(),bound.Bottom()),color);
	LineDDA(CPosition(bound.Right(),bound.Top()),CPosition(bound.Right(),bound.Bottom()),color);
	LineDDA(CPosition(bound.Left(),bound.Bottom()),CPosition(bound.Right(),bound.Bottom()),color);
}

void CGraphics::FillBoud( const CBound& bound ,COLORARGB color )
{
	CImageBuffer buffer;
	buffer.Initialize(1,1,false);
	buffer.ClearColor(color);
	DrawImage_Repeat(&buffer,CBound(),bound);
}



