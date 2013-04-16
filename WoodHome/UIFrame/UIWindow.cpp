#include "UIWindow.h"
#include "FileSystem.h"
#include "SceneManager.h"
#include "ImageBuffer.h"
#include "Graphics.h"

CUIWindow::CUIWindow(Style_Window id)
{
	mSceneManager = new CSceneManager(this);
	mHeight = 1024;
	mWidth = 1024;
	mStartSceneID = SCENE_Start;
	mFramebuffer = new CImageBuffer;
	mFramebuffer->Initialize(mWidth , mHeight , false);
	mGraphic = new CGraphics(mFramebuffer);
}


CUIWindow::~CUIWindow(void)
{
	delete mGraphic;
	delete mFramebuffer;
	delete mSceneManager;
}



