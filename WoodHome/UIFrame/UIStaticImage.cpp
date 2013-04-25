#include "UIStaticImage.h"
#include "ImageBuffer.h"
#include "ImageResouceMgr.h"
#include "Graphics.h"
#include "Transfrom.h"
#include "SlimXml.h"

CUIStaticImage::CUIStaticImage(void) : 
mCenterX(0),
mCenterY(0),
mSkewX(0.0f),
mSkewY(0.0f),
mScaleX(1.0f),
mScaleY(1.0f),
mImageID(Invalid)
{
}


CUIStaticImage::~CUIStaticImage(void)
{
}

//
//<StaticImage name = "image" order = "1" visible = "true" x = "10" y = "10" iamge = "1" scalex = "1.0" scaley = "1.0" skewx = "0" skewy = "0"/>
//scalex scaley default value 1.0f
//skewx skewy default value 0.0f
void CUIStaticImage::Load( const slim::XmlNode* node )
{
	CUIObject::Load(node);
	mSkewX = node->readAttributeAsFloat("skewx");
	mSkewY = node->readAttributeAsFloat("skewy");
	mScaleX = node->readAttributeAsFloat("scalex" , 1.0f);
	mScaleY = node->readAttributeAsFloat("scaley" , 1.0f);
	mCenterX = node->readAttributeAsInt("x");
	mCenterY = node->readAttributeAsInt("y");
	mImageID = SourceID(node->readAttributeAsInt("image" , Invalid));
}

void CUIStaticImage::Draw( CGraphics* pGraphic )
{
	CImageBuffer* pbuffer = sImageResource.GetImage(mImageID);
	CTransfrom tf;
	int x = mCenterX;
	int y = mCenterY;
	Parent()->Absolute(x,y);
	tf.SetAnchorPoint(pbuffer->Width()/2.0f,pbuffer->Height()/2.0f);
	tf.SetPosition(float(x) , float(y));
	tf.SetRotation(float(mSkewX) , float(mSkewY));
	tf.SetScale(float(mScaleX) , float(mScaleY));
	tf.Update();
	pGraphic->DrawImage(pbuffer,tf);
}
