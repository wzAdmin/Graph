#include "UIObjectFactory.h"
#include "Scene.h"
#include "UILayer.h"

CUIObjectFactory::CUIObjectFactory(void)
{
	Register("Scene",CScene::Create);
	Register("Layer",CUILayer::Create);
}


CUIObjectFactory::~CUIObjectFactory(void)
{
}

CUIObject* CUIObjectFactory::CreateObject( const char* name )
{
	FunctionIterator it = mCreatFuns.find(name);
	if(mCreatFuns.end() != it)
		return (*it->second)();
	return NULL;
}

void CUIObjectFactory::Register( const char* name , ObjCreatFun func )
{
	FunctionIterator it = mCreatFuns.find(name);
	if(mCreatFuns.end() == it)
		mCreatFuns.insert(FunctionPair(name,func));
}
