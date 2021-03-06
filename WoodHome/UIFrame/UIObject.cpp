#include "UIObject.h"
#include "SlimXml.h"

CUIObject::CUIObject(void):
mIsInputMode(false),
mParent(NULL),
mOrder(0),
mIsVisible(true)
{
}


CUIObject::~CUIObject(void)
{
}

void CUIObject::InputMode( bool val )
{
	mIsInputMode = val;
	CUIObject* parent = mParent;
	while (parent)
	{
		parent->InputMode(val);
		parent = parent->Parent();
	}
}

void CUIObject::Load( const slim::XmlNode* node )
{
	mOrder = node->readAttributeAsInt("order");
	mIsVisible = node->readAttributeAsBool("visible");
	mBound.Left(node->readAttributeAsInt("x"));
	mBound.Top(node->readAttributeAsInt("y"));
	mBound.Right(mBound.Left() - 1 + node->readAttributeAsInt("width"));
	mBound.Bottom(mBound.Top() - 1 + node->readAttributeAsInt("height"));
	mName = node->readAttributeAsString("name");
}

void CUIObject::Absolute(CBound& bound)
{
	SelfToParent(bound);
	if(mParent)
		mParent->Absolute(bound);
}

CPosition CUIObject::Absolute( int x ,int y )
{
	CPosition pt = SelfToParent(x,y);
	if(mParent)
		return mParent->SelfToParent(pt.X() , pt.Y());
	return pt;
}

void CUIObject::SelfToParent( CBound& bound )
{
	bound.Move(mBound.Left() , mBound.Top());
}

CPosition CUIObject::SelfToParent( int x ,int y )
{
	return CPosition(x + mBound.Left() , y + mBound.Top());
}

void CUIObject::ParentToSelf( CBound& bound )
{
	bound.Move(-mBound.Left() , -mBound.Top());
}

CPosition CUIObject::ParentToSelf( int x ,int y )
{
	return CPosition(x - mBound.Left() , y - mBound.Top());
}

void CUIObject::DrawToWindow(const CBound* bd/* = NULL*/)
{
	if(mParent)
	{
		if(bd)
		{
			CBound parentBd =*bd;
			SelfToParent(parentBd);
			mParent->DrawToWindow(&parentBd);
		}
		else
			mParent->DrawToWindow(&mBound);
	}
}

bool CUIObject::IsRealVisible()
{
	if(mParent)
		return mParent->IsRealVisible();
	return mIsVisible;
}

CUIObject* CUIObject::Root()
{
	if(mParent)
		return mParent->Root();
	return this;
}
