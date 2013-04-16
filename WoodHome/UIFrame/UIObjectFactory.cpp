#include "UIObjectFactory.h"


CUIObjectFactory::CUIObjectFactory(void)
{
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
	if(mCreatFuns.end() != it)
		mCreatFuns.insert(FunctionPair(name,func));
}
