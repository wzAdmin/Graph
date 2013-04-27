#pragma once
#include "UIDataAdapter.h"
#include <vector>
#include <string>

class CTestAdapter :
	public CUIDataAdapter
{
public:
	CTestAdapter(void);
	~CTestAdapter(void);
private:
	virtual void SetData(CUIObject* pUIObj ,unsigned int index) const;
	virtual unsigned int Count() const {return mVecStr.size();}

	std::vector<std::wstring> mVecStr;
};
