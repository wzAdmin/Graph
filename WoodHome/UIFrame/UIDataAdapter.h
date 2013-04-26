#pragma once

class CUIObject;
class UI_API CUIDataAdapter
{
public:
	CUIDataAdapter(void){}
	virtual ~CUIDataAdapter(void){}
public:
	virtual void SetData(CUIObject* pUIObj , int index) const = 0 ;
	virtual unsigned int Count() const = 0;
};

