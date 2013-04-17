
#include "UIFrame.h"
#include "UIContainer.h"
#include "SlimXml.h"
#include "UIObjectFactory.h"

CUIContainer::CUIContainer(void)
{
}


CUIContainer::~CUIContainer(void)
{
}

void CUIContainer::Draw( CGraphics* pGraphic )
{
	DrawSelf(pGraphic);
	for (unsigned int i = mChilds.size(); i ; i--)
	{
		if(mChilds[i-1]->Visible())
			mChilds[i-1]->Draw(pGraphic);
	}
}

void CUIContainer::AddChild( CUIObject* child )
{
	assert(NULL == child->Parent());
	child->Parent(this);
	mChilds.push_back(child);
	unsigned int i = mChilds.size() - 1;
	while (i)
	{
		if(child->Order() < mChilds[i-1]->Order())
		{
			mChilds[i] = mChilds[i-1];
			i--;
		}
		else
			break;
	}
	mChilds[i] = child;
}

void CUIContainer::Clear()
{
	for (unsigned int i  = 0 ; i <  mChilds.size(); i++)
		delete mChilds[i];
	mChilds.clear();
}

void CUIContainer::Load( const slim::XmlNode* node )
{
	LoadSelf(node);
	slim::NodeIterator it;
	slim::XmlNode* child = node->getFirstChild(it);
	for(; child ; child = node->getNextChild(it))
	{
		CUIObject* obj = sUIFrame.GetObjFactory()->CreateObject(child->getName());
		if(obj)
		{
			AddChild(obj);
			obj->Load(child);
		}
	}
}

bool CUIContainer::OnInputChar( const wchar_t* wcs,int len )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		if(mChilds[i]->OnInputChar(wcs,len))
			return true;
	}
	return false;
}

bool CUIContainer::OnLBtnDown( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(pt.X() , pt.Y()) && mChilds[i]->OnLBtnDown(pt.X() , pt.Y()))
			return true;
	}
	return false;
}

bool CUIContainer::OnLBtnUp( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(pt.X() , pt.Y()) && mChilds[i]->OnLBtnUp(pt.X() , pt.Y()))
			return true;
	}
	return false;
}

bool CUIContainer::OnMouseMove( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(pt.X() , pt.Y()) && mChilds[i]->OnMouseMove(pt.X() , pt.Y()))
			return true;
	}
	return false;
}

bool CUIContainer::OnRBtnDown( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(pt.X() , pt.Y()) && mChilds[i]->OnRBtnDown(pt.X() , pt.Y()))
			return true;
	}
	return false;
}

bool CUIContainer::OnRBtnUp( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(pt.X() , pt.Y()) && mChilds[i]->OnRBtnUp(pt.X() , pt.Y()))
			return true;
	}
	return false;
}
