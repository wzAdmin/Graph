#include "UILayer.h"
#include "SlimXml.h"
#include "FileSystem.h"
#include "ImageResouceMgr.h"
#include "Graphics.h"

CUILayer::CUILayer(void)
{
}


CUILayer::~CUILayer(void)
{
}

void CUILayer::LoadFromFile( SourceID id )
{
	Sourceitem item = sFilesystem.GetSource(id);
	assert(item.format == FM_SCENE || item.format == FM_LAYER);
	char* data = new char[item.length];
	sFilesystem.LoadSource(item,data);
	slim::XmlDocument doc;
	doc.loadFromMemory(data,item.length);
	slim::NodeIterator it;
	slim::XmlNode* root = doc.getFirstChild(it);
	CUIContainer::Load(root);
	delete[] data;
}

void CUILayer::LoadSelf( const slim::XmlNode* node )
{
	CUIObject::Load(node);
	mImageId = SourceID(node->readAttributeAsInt("bgImage",Invalid));
}

void CUILayer::Load( const slim::XmlNode* node )
{
	LoadSelf(node);
	LoadFromFile(SourceID(node->readAttributeAsInt("Source")));
}

void CUILayer::DrawSelf( CGraphics* pGraphic )
{
	if(Invalid == mImageId)
		return;
	CImageBuffer* pImage = sImageResource.GetImage(mImageId);
	if(pImage)
	{
		CBound bd = Bound();
		ParentToSelf(bd);
		Absolute(bd);
		pGraphic->DrawImage_Repeat(pImage,CBound(0,pImage->Width() - 1,0 ,pImage->Height() - 1),bd);
	}
}
