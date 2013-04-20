#pragma once
#include "UIWindow.h"
#include <map>
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
	void Exit();
private:
	CUIObjectFactory* mObjFactory;
	typedef std::map<WindID,CUIWindow*>::iterator WinIterator;
	std::map<WindID,CUIWindow*> mWinds;
	int mValidID;
};

#define sUIFrame CUIFrame::Instance()
