#include "SceneManager.h"
#include "Scene.h"
#include "FileSystem.h"
#include "SlimXml.h"
#include "UIFrame.h"
#include "UIObjectFactory.h"
#include "Memory_Check.h"
#include "Graphics.h"
#include "EffectFadeto.h"

CSceneManager::CSceneManager(CUIWindow* wnd):mWind(wnd),mEffect(NULL)
{
}


CSceneManager::~CSceneManager(void)
{
	SceneMapItor it = mScenes.begin();
	for ( ; mScenes.end() != it ; it++)
	{
		DELETE_LEAKCHECK(it->second);
	}
	if(mEffect)
		DELETE_LEAKCHECK(mEffect);
}

void CSceneManager::GoTo( SourceID toid ,CScene* from /*= 0*/ ,void* data/* = NULL*/)
{
	mParam_Onshow = data;
	// hide from
	if(from)
	{
		from->Visible(false);
		from->OnHide();
		from->Notify();
	}
	SceneMapItor it = mScenes.find(toid);
	CScene* pTo = NULL;

	//created already
	if(mScenes.end() != it)
	{

		SceneListItor itor = mSceneStack.begin();
		for( ; mSceneStack.end() != itor && (*itor) != it->second ; itor++);
		if(mSceneStack.end() != itor)
			mSceneStack.erase(itor);
		pTo = it->second;
		mSceneStack.push_back(pTo);
	}
	else// has not created so create a new
	{
		pTo = CreatScene(toid);
		mScenes.insert(std::pair<SourceID,CScene*>(toid,pTo));
		pTo->Visible(false);
		mSceneStack.push_back(pTo);
	}

	//deal effect
	if(!from)
	{
		pTo->Visible(true);
		pTo->OnShow(mParam_Onshow);
		pTo->DrawToWindow();
	}
	else
	{
		mEffect = NEW_LEAKCHECK CEffectFadeto(this,50,10,mWind->Graphic());
		mEffect->Start(from , pTo);
	}
}

CScene* CSceneManager::GetCurScene()
{
	assert(!mSceneStack.empty());
	return mSceneStack.back();
}

CScene* CSceneManager::CreatScene( SourceID sceneid )
{
	Sourceitem item = sFilesystem.GetSource(sceneid);
	char* pdata = NEW_LEAKCHECK char[item.length];
	sFilesystem.LoadSource(item,pdata);
	slim::XmlDocument doc;
	doc.loadFromMemory(pdata,item.length);
	DELETEARR_LEAKCHECK(pdata);
	slim::NodeIterator nodeit ;
	slim::XmlNode* child = doc.getFirstChild(nodeit);
	CScene* pScene = (CScene*)sUIFrame.GetObjFactory()->CreateObject(child->getName());
	pScene->Load(child);
	pScene->SetWind(mWind);
	return pScene;
}

void CSceneManager::Back(void* data /*= NULL*/)
{
	mParam_Onshow = data;
	if(1==mSceneStack.size())
		printf("left scene < 2 can not Back\n");
	else
	{
		CScene* pcur = mSceneStack.back();
		pcur->Visible(false);
		pcur->OnHide();
		mSceneStack.pop_back();
		mEffect = NEW_LEAKCHECK CEffectFadeto(this,50,20,mWind->Graphic());
		mEffect->Start(pcur , mSceneStack.back());
	}
}

void CSceneManager::OnDestroy()
{
	SceneMapItor it = mScenes.begin();
	for ( ; mScenes.end() != it ; it++)
	{
		it->second->OnUnload();
	}
}

void CSceneManager::OnEffect()
{
	mWind->BufferToWindow(mWind->Graphic()->GetImage());
}

void CSceneManager::OnEffectEnd( CScene* src , CScene* dest )
{
	dest->Visible(true);
	dest->OnShow(mParam_Onshow);
	dest->DrawToWindow();
	DELETE_LEAKCHECK(mEffect);
	mEffect = NULL;
}
