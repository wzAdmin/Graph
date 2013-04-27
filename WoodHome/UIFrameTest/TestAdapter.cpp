#include "TestAdapter.h"
#include "UITextView.h"

CTestAdapter::CTestAdapter(void)
{
	mVecStr.push_back(L"daa1");
	mVecStr.push_back(L"daa2");
	mVecStr.push_back(L"daa3");
	mVecStr.push_back(L"daa4");
	mVecStr.push_back(L"daa5");
	mVecStr.push_back(L"daa6");
	mVecStr.push_back(L"daa7");
	mVecStr.push_back(L"daa8");
	mVecStr.push_back(L"daa9");
	mVecStr.push_back(L"daa10");
}

CTestAdapter::~CTestAdapter(void)
{
}

void CTestAdapter::SetData( CUIObject* pUIObj , unsigned int index ) const
{
	CUITextView* textView = (CUITextView*)pUIObj;
	assert(index < mVecStr.size());
	textView->Text(mVecStr[index]);
}
