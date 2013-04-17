#include "UIWindow.h"
#include "FileSystem.h"
#include "SceneManager.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "Scene.h"
CUIWindow::CUIWindow(Style_Window id)
{
	mSceneManager = new CSceneManager(this);
	mHeight = 700;
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

void CUIWindow::DispatchSysMessage( const SystemMessage& msg )
{
	switch (msg.msg)
	{
	case LBtnDown:
		mSceneManager->GetCurScene()->OnLBtnDown(msg.lParam , msg.wParam);
		break;
	case LBtnUp:
		mSceneManager->GetCurScene()->OnLBtnUp(msg.lParam , msg.wParam);
		break;
	case RBtnDown:
		mSceneManager->GetCurScene()->OnRBtnDown(msg.lParam , msg.wParam);
		break;
	case RBtnUp:
		mSceneManager->GetCurScene()->OnRBtnUp(msg.lParam , msg.wParam);
		break;
	case MouseMove:
		mSceneManager->GetCurScene()->OnMouseMove(msg.lParam , msg.wParam);
		break;
	case CharInput:
		mSceneManager->GetCurScene()->OnInputChar((const wchar_t*)msg.lParam , msg.wParam);
		break;
	default:
		break;
	}
}



