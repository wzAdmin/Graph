#include "UIFrame.h"
#include "Wind_win32.h"
#include "UIObjectFactory.h"
#include "FileSystem.h"

CUIFrame::CUIFrame(void):mValidID(0)
{
	mObjFactory = new CUIObjectFactory();
	sFilesystem.Open("Out/Image");
}


CUIFrame::~CUIFrame(void)
{
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
		delete it->second;
		mWinds.erase(it);
	}
}

void CUIFrame::StartWindow( Style_Window id )
{
#ifdef WIN32
	CWind_win32* pWind = new CWind_win32(id);
	mWinds.insert(std::pair<WindID,CUIWindow*>(pWind->GetWindID(),pWind));
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
