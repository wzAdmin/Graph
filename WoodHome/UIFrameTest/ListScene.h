#pragma once
#include "scene.h"

class CUIButton;
class CUIList;
class CTestAdapter;
class CListScene :
	public CScene
{
public:
	CListScene(void);
	~CListScene(void);
	static CUIObject* Create(){return NEW_LEAKCHECK CListScene;}
private:
	virtual void OnLoad();
	void OnNext();
	void OnPrev();
	void OnBack();
private:
	CTestAdapter* mListAdapter;
	CUIList* mList;
	CUIButton* mPrev;
	CUIButton* mNext;
};
