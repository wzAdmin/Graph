#pragma once
#include <map>
#include <string>
#include "UItype.h"

class CUIObject;
typedef CUIObject* (*ObjCreatFun)();

class UI_API CUIObjectFactory
{
public:
	CUIObjectFactory(void);
	~CUIObjectFactory(void);
public:
	void Register(const char* name , ObjCreatFun func);
	CUIObject* CreateObject(const char* name);
private:
	typedef std::map<std::string,ObjCreatFun>::iterator FunctionIterator;
	typedef std::pair<std::string,ObjCreatFun> FunctionPair;
	std::map<std::string,ObjCreatFun> mCreatFuns;
};

