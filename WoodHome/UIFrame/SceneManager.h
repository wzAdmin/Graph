#pragma once
#include "resource_image.h"
#include "UItype.h"
#include "EffectType.h"
#include "SceneEffect.h"
#include <map>
#include <list>

class CBound;
class CScene;
class CGraphics;
class CUIWindow;
class UI_API CSceneManager : public IEffectListner
{
public:
	CSceneManager(CUIWindow* wnd);
	~CSceneManager(void);
public:
	CScene* GetCurScene();
	CScene* GetCurMsgScene();
	void GotoAsDialog(SourceID sceneid , void* data = NULL);
	void GoTo(SourceID toid ,CScene* from = 0,void* data = NULL , EffectType effect = Effect_Invalid);
	void Back(void* data = NULL, EffectType effect = Effect_Invalid);
	bool DrawScene(CGraphics* pGraphic ,const CBound* drawBound = NULL);
	void OnDestroy();
private:
	virtual void OnEffect();
	virtual void OnEffectEnd(CScene* src , CScene* dest);
	CScene* CreatScene(SourceID sceneid);
private:
	CUIWindow* mWind;
	typedef std::map<SourceID,CScene*>::iterator SceneMapItor;
	typedef std::list<CScene*>::iterator SceneListItor;
	std::map<SourceID , CScene*> mScenes;
	std::list<CScene*> mSceneStack;
	CScene* mCurDialog;
	CSceneEffect* mEffect;
	void* mParam_Onshow;
};

