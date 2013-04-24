#pragma once
#include "uiobject.h"
#include "resource_image.h"

class UI_API CUIStaticImage :
	public CUIObject
{
public:
	static CUIObject* Create(){ return NEW_LEAKCHECK CUIStaticImage;}
	CUIStaticImage(void);
	~CUIStaticImage(void);
public:
	void SetCenter(int x , int y){mCenterX = x; mCenterY = y;}
	void SetScale(float scalex , float scaley){mScaleX = scalex ; mScaleY = scaley;}
	void SetSkew(float skewx , float skewy){mScaleX = skewx ; mSkewY = skewy;}
	void Rotate(float x , float y){mSkewX += x; mSkewY += y;}
private:
	virtual void Load(const slim::XmlNode* node);
	virtual void Draw(CGraphics* pGraphic);
private:
	int mCenterX;
	int mCenterY;
	SourceID mImageID;
	float mScaleX;
	float mScaleY;
	float mSkewX;
	float mSkewY;
};

