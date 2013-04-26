#include "UIList.h"
#include "UIDataAdapter.h"

CUIList::CUIList(void)
{
}


CUIList::~CUIList(void)
{
}

void CUIList::SetData( const CUIDataAdapter* data )
{
	mCurIndex = 0;
	mCountPerPage = mChilds.size();
	mAdaper = data;
	for (unsigned int i = 0 ; i < mChilds.size() && i < mAdaper->Count(); i++)
	{
		mAdaper->SetData(mChilds[i] , i);
	}
}

void CUIList::Prev()
{
	if(0 == mCurIndex)
		return;
	mCurIndex -= mCountPerPage; 
	UpdateList();
}

void CUIList::Next()
{
	if(mCountPerPage + mCurIndex >= mAdaper->Count())
		return ;
	mCurIndex += mCountPerPage;
	UpdateList();
}

void CUIList::UpdateList()
{
	unsigned int valiableCount = mAdaper->Count() - mCurIndex;
	valiableCount = MIN(valiableCount , mChilds.size());
	for (unsigned int i = 0 ; i < valiableCount; i++)
	{
		mChilds[i]->Visible(true);
		mAdaper->SetData(mChilds[i] , mCurIndex + i);
	}
	for (unsigned int i = valiableCount ; i < mChilds.size() ; i++)
	{
		mChilds[i]->Visible(false);
	}
	DrawToWindow();
}
