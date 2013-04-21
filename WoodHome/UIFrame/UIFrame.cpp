#include "UIFrame.h"
#include "Wind_win32.h"
#include "UIObjectFactory.h"
#include "FileSystem.h"
#include "SceneManager.h"
#include "Scene.h"
#include "WindConfig.h"
#include "Trace.h"
#include "TimerManager.h"

CUIFrame::CUIFrame(void):mValidID(0),mbRunning(false)
{
	mObjFactory = new CUIObjectFactory();
	sFilesystem.Open("Out/Image");
	mWindConfig = new CWindConfig;
	mTimerMgr = new CTimerManager;
}


CUIFrame::~CUIFrame(void)
{
	delete mTimerMgr;
	delete mWindConfig;
	WinIterator it = mWinds.begin();
	for( ; mWinds.end() != it ; it++)
		delete it->second;
	delete mObjFactory;
}

CUIFrame& CUIFrame::Instance()
{
	static CUIFrame frame;
	return frame;
}

void CUIFrame::EndWindow( WindID id )
{
	WinIterator it = mWinds.find(id);
	if(mWinds.end() != it)
	{
		mWindwosTobeDelete.push_back(it->second);
		mWinds.erase(it);
	}
}

void CUIFrame::StartWindow( Style_Window id )
{
#ifdef WIN32
	CUIWindow* pWind = new CWind_win32(id);
	mWinds.insert(std::pair<WindID,CUIWindow*>(pWind->GetID(),pWind));
	((CUIWindow*)pWind)->Start();
#else
#error("UIFrame::StartWindow not implement");
#endif
}

CUIWindow* CUIFrame::GetWindow( WindID id )
{
	WinIterator it = mWinds.find(id);
	if(mWinds.end() != it)
		return it->second;
	return NULL;
}


void CUIFrame::Exit()
{
	while(mWinds.size())
	{
		WinIterator it = mWinds.begin();
		it->second->Quit();
	}
	mbRunning = false;
}

void CUIFrame::Run()
{
	if(mbRunning)
		return;
	mbRunning = true;
	MSG msg;
	while (mbRunning)
	{
		while (mWindwosTobeDelete.size())
		{
			delete mWindwosTobeDelete.front();
			mWindwosTobeDelete.pop_front();
		}
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		mTimerMgr->TimerUpdate();
		Sleep(20);
	}
	while (mWindwosTobeDelete.size())
	{
		delete mWindwosTobeDelete.front();
		mWindwosTobeDelete.pop_front();
	}
}

void CUIFrame::AddWindowToDelete( CUIWindow* pwnd )
{
	if(pwnd)
	{
		pwnd->OnDestroy();
		WinIterator it = mWinds.find(pwnd->GetID());
		if(mWinds.end() != it)
		{
			mWindwosTobeDelete.push_back(it->second);
			mWinds.erase(it);
		}
		else
			assert(false || DebugTrace("no longer should come here!\n"));
	}
}

void CUIFrame::InitWindStyle( SourceID styleconfig )
{
	mWindConfig->Init(styleconfig);
}
