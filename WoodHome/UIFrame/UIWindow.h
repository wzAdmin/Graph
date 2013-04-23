#pragma once
#include "UItype.h"
#include "window_Style.h"
#include "resource_image.h"
typedef int WindID;
class CGraphics;
class CImageBuffer;
class CSceneManager;
class UI_API CUIWindow
{
public:
	CUIWindow(Style_Window id);
	virtual ~CUIWindow(void);
	virtual void MessageTo(WindID windowId,const SystemMessage& msg ) = 0;
	virtual void ShowWindow() = 0;
	virtual void HideWindow() = 0;
	virtual void Minimize() = 0;
	virtual void SetPostion(int x , int y) = 0;
	virtual void DrawToWindow() = 0;
	virtual void BufferToWindow(const CImageBuffer* buffer) = 0;
	virtual void Start() = 0;
	virtual WindID GetID() = 0;
	virtual void Quit() = 0;
	virtual void OnDestroy();
	void DispatchSysMessage(const SystemMessage& msg);
	CGraphics* Graphic() {return mGraphic;}
public:
	CSceneManager* GetSceneMgr(){return mSceneManager;}
protected:
	CGraphics* mGraphic;
	CImageBuffer* mFramebuffer;
	CSceneManager* mSceneManager;
	int mPositionX;
	int mPositionY;
	int mWidth;
	int mHeight;
	SourceID mStartSceneID;
};

