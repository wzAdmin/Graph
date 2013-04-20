#pragma once
#include "UIWindow.h"
#include <map>
#include <list>

class CWindConfig;
class CUIObjectFactory;
class UI_API CUIFrame
{
private:
	CUIFrame(void);
	~CUIFrame(void);
public:
	static CUIFrame& Instance();
	CUIObjectFactory* GetObjFactory()const{ return mObjFactory;}
	void StartWindow(Style_Window id);
	void EndWindow(WindID id);
	CUIWindow* GetWindow(WindID id);
	void Run();
	void Exit();
	int WndCount(){return mWinds.size();}
	void AddWindowToDelete(CUIWindow* pwnd);
	void InitWindStyle(SourceID styleconfig);
	CWindConfig* GetWindCof(){return mWindConfig;}
private:
	CUIObjectFactory* mObjFactory;
	typedef std::map<WindID,CUIWindow*>::iterator WinIterator;
	std::map<WindID,CUIWindow*> mWinds;
	int mValidID;
	std::list<CUIWindow*> mWindwosTobeDelete;
	CWindConfig* mWindConfig;
};

#define sUIFrame CUIFrame::Instance()
