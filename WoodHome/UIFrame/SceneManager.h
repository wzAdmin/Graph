#pragma once
#include "resource_image.h"
#include "UItype.h"
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
private:
	CUIWindow* mWind;
	CScene* mScene;
};

