#include "UIFrame.h"
#include "Wind_win32.h"
#include "UIObjectFactory.h"
#include "FileSystem.h"
#include "SceneManager.h"
#include "Scene.h"

CUIFrame::CUIFrame(void):mValidID(0)
{
	mObjFactory = new CUIObjectFactory();
	sFilesystem.Open("Out/Image");
}


CUIFrame::~CUIFrame(void)
{
	WinIterator it = mWinds.begin();
	for( ; mWinds.end() != it ; it++)
	{
		CUIWindow* pWnd = it->second;
		mWinds.erase(it);
		delete pWnd;
	}
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
		CUIWindow* pWnd = it->second;
		mWinds.erase(it);
		delete pWnd;
	}
}

void CUIFrame::StartWindow( Style_Window id )
{
#ifdef WIN32
	CUIWindow* pWind = new CWind_win32(id);
	mWinds.insert(std::pair<WindID,CUIWindow*>(pWind->GetID(),pWind));
	((CUIWindow*)pWind)->Run();
#else
	error("not implement");
#endif
}

CUIWindow* CUIFrame::GetWindow( WindID id )
{
	WinIterator it = mWinds.find(id);
	if(mWinds.end() != it)
		return it->second;
	return NULL;
}

void CUIFrame::DestroyWnd( CUIWindow* pWnd )
{
	if(pWnd)
		EndWindow(pWnd->GetID());
}
