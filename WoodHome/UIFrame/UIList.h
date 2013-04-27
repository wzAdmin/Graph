#pragma once
#include "uicontainer.h"

class CUIDataAdapter;
class UI_API CUIList :
	public CUIContainer
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CUIList;}
	CUIList(void);
	~CUIList(void);
public:
	void SetData(const CUIDataAdapter* data);
	void Prev();
	void Next();
	bool CanPrev();
	bool CanNext();
private:
	virtual void DrawSelf(CGraphics* pGraphic){}
	virtual void LoadSelf(const slim::XmlNode* node);
	void UpdateList() ;
private:
	unsigned int mCountPerPage;
	unsigned int mCurIndex;
	const CUIDataAdapter* mAdaper;
};

