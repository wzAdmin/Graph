#pragma once
#include "UItype.h"
class  UI_API IMessageDealer
{
public:
	virtual bool OnMouseMove(int x ,int y){return false;}
	virtual bool OnLBtnDown(int x ,int y){return false;}
	virtual bool OnLBtnUp(int x ,int y){return false;}
	virtual bool OnRBtnUp(int x ,int y){return false;}
	virtual bool OnRBtnDown(int x ,int y){return false;}
	virtual bool OnInputChar(const wchar_t* wcs,int len){return false;}
};