#pragma once
#include "GraphicType.h"
#include "Position.h"
#include "Bound.h"
#include "ClipUtils.h"
#include "ImageBuffer.h"
class CImageBuffer;
class CTransfrom;
class GRAPHIC_API CGraphics
{
public:
	CGraphics(CImageBuffer* image);
	~CGraphics(void);
public:
	void Initialize(CImageBuffer* image);
	int Width() const{return mWidth;}
	int Height() const{return mHeight;}
	int Stride() const{return mImagebuffer->Stride();}
public:
	const CImageBuffer* GetImage() const {return mImagebuffer;}
	void ClearColor(COLORARGB color){mImagebuffer->ClearColor(color);}
	void DrawCirce(CPosition center ,int R ,COLORARGB color);
	void Polygon(const CPosition* points , int pointCount,COLORARGB color);
	void Line(CPosition A , CPosition B ,int Width ,COLORARGB color);
	void LineDDA(CPosition A , CPosition B  ,COLORARGB color);
	void LineDDA(CPosition A , CPosition B ,int width ,COLORARGB color);
	void LineDDA(CPosition A ,int width1 ,CPosition B , int width2,COLORARGB color);
	void DrawImage(const CImageBuffer* pImage ,const CTransfrom& tf ,const CBound* srcBound = NULL,const CBound* clipBuond = NULL);
	void DrawImage(const CGrayImage* pImage , const CTransfrom& tf ,COLORARGB color,const CBound* srcBound = NULL,const CBound* clipBuond = NULL);
	void DrawImage_Repeat(const CImageBuffer* pImage , const CBound& srcBound , const CBound& destBound);
	void DrawImage_Scale(const CImageBuffer* pImage , const CBound& srcBound , const CBound& destBound);
	void DrawTextW(const wchar_t* str ,int left , int bottom,const Font& ft,const CBound* clipBuond = NULL);
	void DrawTextW(const wchar_t* str ,const CBound& dest, const Font& ft,ALIGN align);
	void DrawTextW(const wchar_t* str ,int left , int bottom,const Font& ft, float rotation,const CBound* clipBuond = NULL );
	void DrawTextW(const wchar_t* str ,const CPosition* pts,int ptsCount,const Font& ft, float space, float firstDis = .0f,bool loop = false);
	void DrawBound(const CBound& bound , COLORARGB color);
	void FillBoud(const CBound& bound ,COLORARGB color);
private:
	CPosition GetAlignPostion(const CBound& dest, const CBound& src,ALIGN align);
	void DrawGrayImage(const CGrayImage* pImage,const CBound& srcBound , const CBound& destBound,COLORARGB color);

private:
	CImageBuffer* mImagebuffer;
	int mWidth;
	int mHeight;
	COLORFORMAT mFormat;
	unsigned short* mpFrambuffer;
	CClipUtils* mClip;
};

