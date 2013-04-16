#pragma once
#include "GraphicType.h"
class GRAPHIC_API CGrayImage
{
public:
	CGrayImage(int width ,int height);
	~CGrayImage();
public:
	void Set(unsigned char* pData,int width,int height,int x,int y);
	const unsigned char* GetPixels() const {return mData;}
	int Width() const {return mWidth;}
	int Height() const {return mHeight;}
private:
	unsigned char* mData;
	int mWidth;
	int mHeight;
};
class GRAPHIC_API CImageBuffer
{
public:
	CImageBuffer(void);
	virtual ~CImageBuffer(void);
public:
	virtual void LoadFromMem(const char* data , int len){}
	void Load(const char* path);
	const unsigned short* GetPixels() const {return mData;}
	const unsigned char* GetAlpha()const {return mAlpha;}
	int Width() const {return mWidth;}
	int Height() const {return mHeight;}
	int Stride() const{return ((mWidth + 1)>>1)<<1;}
	void Initialize(int width , int height , bool hasAlpha);
	void ClearColor(COLORARGB color);
protected:
	unsigned short* mData;
	unsigned char* mAlpha;
	int mWidth;
	int mHeight;
};

class GRAPHIC_API CImage_PNG : public CImageBuffer
{
public:
	CImage_PNG();
	~CImage_PNG();
public:
	virtual void LoadFromMem(const char* data , int len);
private:
	void To565(const char* data);
};

class GRAPHIC_API CImage_JPG : public CImageBuffer
{
public:
	CImage_JPG();
	~CImage_JPG();
public:
	virtual void LoadFromMem(const char* data , int len);
private:
	void To565(const char* data);
};