#pragma once
#include "UILayer.h"
class CUIWindow;
class UI_API CScene :
	public CUILayer
{
	typedef void (CScene::*NotifyFormerOnHide)(void* data);
	friend class CSceneManager;
public:
	CScene();
	~CScene(void);
	static CUIObject* Create(){return NEW_LEAKCHECK CScene;}
public:
	virtual void Draw(CGraphics* pGraphic);
	virtual void DrawToWindow();
	virtual void OnShow(void* data = NULL){}

	// the OnUnload will be called when the window which the scene belong to destroyed
	virtual void OnUnload(){}

	//call mNotifyFunc to notify the listener
	//why not call in OnHide()?
	//because when OnHide not always needs notify the listener such as Back
	//not call mNotifyFunc in base class as I do not know the param yet
	virtual void Notify(){}

	virtual void OnHide(void* data = NULL){}
	virtual void SetNotify(NotifyFormerOnHide func){mNotifyFunc = func;}
	void SetWind(CUIWindow* Wnd){mWind = Wnd;}
	void Goto(SourceID toScene,void* data = NULL);
	void Back();
protected:
	NotifyFormerOnHide mNotifyFunc;
protected:
	CUIWindow* mWind;
	CScene* mFrom;
};

