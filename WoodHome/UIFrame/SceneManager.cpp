#include "SceneManager.h"
#include "Scene.h"
#include "FileSystem.h"
#include "SlimXml.h"
#include "UIFrame.h"
#include "UIObjectFactory.h"

CSceneManager::CSceneManager(CUIWindow* wnd):mWind(wnd)
{
}


CSceneManager::~CSceneManager(void)
{
	SceneMapItor it = mScenes.begin();
	for ( ; mScenes.end() != it ; it++)
	{
		delete it->second;
	}
}

void CSceneManager::GoTo( SourceID toid ,CScene* from /*= 0*/ )
{
	if(from)
		from->Visible(false);
	SceneMapItor it = mScenes.find(toid);
	if(mScenes.end() != it)
	{
		it->second->Visible(true);
		SceneListItor itor = mSceneStack.begin();
		for( ; mSceneStack.end() != itor && (*itor) != it->second ; itor++);
		if(mSceneStack.end() != itor)
		{
			(*itor)->DrawToWindow();
			mSceneStack.push_back((*itor));
			mSceneStack.erase(itor);
		}
		return ;
	}
	CScene* pScene = CreatScene(toid);
	mScenes.insert(std::pair<SourceID,CScene*>(toid,pScene));
	pScene->Visible(true);
	mSceneStack.push_back(pScene);
	pScene->DrawToWindow();
}

CScene* CSceneManager::GetCurScene()
{
	assert(!mSceneStack.empty());
	return mSceneStack.back();
}

CScene* CSceneManager::CreatScene( SourceID sceneid )
{
	Sourceitem item = sFilesystem.GetSource(sceneid);
	char* pdata = new char[item.length];
	sFilesystem.LoadSource(item,pdata);
	slim::XmlDocument doc;
	doc.loadFromMemory(pdata,item.length);
	delete[] pdata;
	slim::NodeIterator nodeit ;
	slim::XmlNode* child = doc.getFirstChild(nodeit);
	CScene* pScene = (CScene*)sUIFrame.GetObjFactory()->CreateObject(child->getName());
	pScene->Load(child);
	pScene->SetWind(mWind);
	return pScene;
}

void CSceneManager::Back()
{
	if(1==mSceneStack.size())
		printf("left scene < 2 can not Back\n");
	else
	{
		CScene* pcur = mSceneStack.back();
		pcur->Visible(true);
		mSceneStack.pop_back();
		mSceneStack.back()->Visible(true);
		mSceneStack.back()->DrawToWindow();
	}
}
