#pragma once
#include "resource_image.h"
#include "UItype.h"
#include <map>
#include <list>
class CScene;
class CUIWindow;
class UI_API CSceneManager
{
public:
	CSceneManager(CUIWindow* wnd);
	~CSceneManager(void);
public:
	CScene* GetCurScene();
	void GoTo(SourceID toid ,CScene* from = 0);
	void Back();
private:
	CScene* CreatScene(SourceID sceneid);
private:
	CUIWindow* mWind;
	typedef std::map<SourceID,CScene*>::iterator SceneMapItor;
	typedef std::list<CScene*>::iterator SceneListItor;
	std::map<SourceID , CScene*> mScenes;
	std::list<CScene*> mSceneStack;
};

