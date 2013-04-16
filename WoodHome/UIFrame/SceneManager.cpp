#include "SceneManager.h"
#include "Scene.h"

CSceneManager::CSceneManager(CUIWindow* wnd):mScene(0),mWind(wnd)
{
}


CSceneManager::~CSceneManager(void)
{
}

void CSceneManager::GoTo( SourceID toid ,CScene* from /*= 0*/ )
{
	mScene = new CScene(mWind);
	mScene->LoadFromFile(toid);
	mScene->DrawToWindow();
}

CScene* CSceneManager::GetCurScene()
{
	return mScene;
}
