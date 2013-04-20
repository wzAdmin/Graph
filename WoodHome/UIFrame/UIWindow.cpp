#include "UIWindow.h"
#include "FileSystem.h"
#include "SceneManager.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "Scene.h"
#include "WindConfig.h"
#include "UIFrame.h"
CUIWindow::CUIWindow(Style_Window id)
{
	const WindowConfig* cf = sUIFrame.GetWindCof()->GetConfig(id);
	mSceneManager = new CSceneManager(this);
	mHeight = cf->height;
	mWidth = cf->width;
	mStartSceneID = cf->startScene;
	mPositionX = cf->x;
	mPositionY = cf->y;
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
	assert(this);
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

void CUIWindow::OnDestroy()
{
	mSceneManager->OnDestroy();
}



