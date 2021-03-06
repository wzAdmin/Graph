
#include "UIFrame.h"
#include "UIContainer.h"
#include "UIObjectFactory.h"
#include "Trace.h"
#include "SlimXml.h"
#include "Graphics.h"

CUIContainer::CUIContainer(void):mFcousedObj(NULL)
{
}


CUIContainer::~CUIContainer(void)
{
	for (unsigned int i = 0; i < mChilds.size(); i++)
		DELETE_LEAKCHECK(mChilds[i]);
}

void CUIContainer::Draw( CGraphics* pGraphic )
{
	DrawSelf(pGraphic);
	CBound clip = pGraphic->GetClipBound();
	for (unsigned int i = mChilds.size(); i ; i--)
	{
		if(mChilds[i-1]->Visible())
		{
			CBound bdchild = mChilds[i-1]->Bound();
			Absolute(bdchild);
			if(CBound::Intersect(clip,bdchild,bdchild))
			{
				pGraphic->SetClipBound(bdchild);
				mChilds[i-1]->Draw(pGraphic);
			}
		}
	}
	pGraphic->SetClipBound(clip);
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
		DELETE_LEAKCHECK(mChilds[i]);
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
		{
			return true;
		}
	}
	return false;
}

bool CUIContainer::OnLBtnDown( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(x ,y) && mChilds[i]->OnLBtnDown(pt.X() , pt.Y()))
		{
			if(mFcousedObj && mFcousedObj != mChilds[i])
			{
				mFcousedObj->OnFocusOut(mChilds[i]);
			}
			mFcousedObj = mChilds[i];
			return true;
		}
	}
	if(mFcousedObj)
	{
		mFcousedObj->OnFocusOut(NULL);
		mFcousedObj = NULL;
	}
	return false;
}

bool CUIContainer::OnLBtnUp( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(x ,y) && mChilds[i]->OnLBtnUp(pt.X() , pt.Y()))
		{
			if(mFcousedObj && mFcousedObj != mChilds[i])
			{
				mFcousedObj->OnFocusOut(mChilds[i]);
			}
			mFcousedObj = mChilds[i];
			return true;
		}
	}
	if(mFcousedObj)
	{
		mFcousedObj->OnFocusOut(NULL);
		mFcousedObj = NULL;
	}
	return false;
}

bool CUIContainer::OnMouseMove( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(x ,y) && mChilds[i]->OnMouseMove(pt.X() , pt.Y()))
		{
			if(mFcousedObj && mFcousedObj != mChilds[i])
			{
				mFcousedObj->OnFocusOut(mChilds[i]);
			}
			mFcousedObj = mChilds[i];
			return true;
		}
	}
	if(mFcousedObj)
	{
		mFcousedObj->OnFocusOut(NULL);
		mFcousedObj = NULL;
	}
	return false;
}

bool CUIContainer::OnRBtnDown( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(x , y) && mChilds[i]->OnRBtnDown(pt.X() , pt.Y()))
		{
			if(mFcousedObj && mFcousedObj != mChilds[i])
			{
				mFcousedObj->OnFocusOut(mChilds[i]);
			}
			mFcousedObj = mChilds[i];
			return true;
		}
	}
	if(mFcousedObj)
	{
		mFcousedObj->OnFocusOut(NULL);
		mFcousedObj = NULL;
	}
	return false;
}

bool CUIContainer::OnRBtnUp( int x ,int y )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		CPosition pt = mChilds[i]->ParentToSelf(x,y);
		if(mChilds[i]->Bound().Contain(x , y) && mChilds[i]->OnRBtnUp(pt.X() , pt.Y()))
		{
			if(mFcousedObj && mFcousedObj != mChilds[i])
			{
				mFcousedObj->OnFocusOut(mChilds[i]);
			}
			mFcousedObj = mChilds[i];
			return true;
		}
	}
	if(mFcousedObj)
	{
		mFcousedObj->OnFocusOut(NULL);
		mFcousedObj = NULL;
	}
	return false;
}


bool CUIContainer::OnKey( const KeyEvent& e )
{
	for (unsigned int i = 0;i < mChilds.size() ; i ++)
	{
		if(mChilds[i]->OnKey(e))
		{
			return true;
		}
	}
	return false;
}

CUIObject* CUIContainer::get( const std::string& name )
{
	for (unsigned int i = 0 ; i < mChilds.size() ; i++)
	{
		if(name == mChilds[i]->Name())
		{
#if defined(DEBUG) || defined(_DEBUG)
			for(unsigned int j = i + 1 ; j < mChilds.size() ; j++)
			{
				if(name == mChilds[j]->Name())
					DebugTrace(Trace_Error,"the name %s has repeated in %s\n",name.c_str(),Name().c_str());
			}
#endif
			return mChilds[i];
		}
	}
	DebugTrace(Trace_Warning,"%s Cant not find %s \n",Name().c_str(),name.c_str());
	return NULL;
}
