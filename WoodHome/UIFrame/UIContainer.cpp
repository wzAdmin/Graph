
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
		if(mChilds[i]->Visible())
			mChilds[i]->Draw(pGraphic);
	}
}

bool CUIContainer::DealMessage( const SystemMessage& message )
{
	switch(message.msg)
	{
	case MouseDown:
	case MouseMove:
	case MouseUp:
		{
			int x = message.wParam , y = message.lParam;
			for (unsigned int i = 0 ; i < mChilds.size() ; i++)
			{
				if(mChilds[i]->Visible())
				{
					const CBound& bd = mChilds[i]->Bound();
					if(bd.Contain(x,y))
					{
						SystemMessage ms = message;
						ms.wParam -= bd.Left();
						ms.lParam -= bd.Top();
						if(mChilds[i]->DealMessage(ms))
							return true;
					}
				}
			}
		}
		break;
	case KeyDown:
	case KeyUp:
	case Char:
		for (unsigned int i = 0 ; i < mChilds.size() ; i++)
		{
				if(mChilds[i]->Visible()&&mChilds[i]->DealMessage(message))
					return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

void CUIContainer::AddChild( CUIObject* child )
{
	assert(NULL == child->Parent());
	child->Parent(this);
	mChilds.push_back(child);
	unsigned int i = mChilds.size() - 1;
	for ( ; i;i--)
	{
		if(child->Order() < mChilds[i-1]->Order())
		{
			mChilds[i] = mChilds[i-1];
		}
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
