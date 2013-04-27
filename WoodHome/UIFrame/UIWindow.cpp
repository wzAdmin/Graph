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
	mSceneManager = NEW_LEAKCHECK CSceneManager(this);
	mHeight = cf->height;
	mWidth = cf->width;
	mStartSceneID = cf->startScene;
	mPositionX = cf->x;
	mPositionY = cf->y;
	mFramebuffer = NEW_LEAKCHECK CImageBuffer;
	mFramebuffer->Initialize(mWidth , mHeight , false);
	mGraphic = NEW_LEAKCHECK CGraphics(mFramebuffer);
}


CUIWindow::~CUIWindow(void)
{
	DELETE_LEAKCHECK(mGraphic);
	DELETE_LEAKCHECK(mFramebuffer);
	DELETE_LEAKCHECK(mSceneManager);
}

void CUIWindow::DispatchSysMessage( const SystemMessage& msg )
{
	assert(this);
	CScene* pScene = mSceneManager->GetCurMsgScene();
	if(pScene && pScene->Visible())
	{
		switch (msg.msg)
		{
		case LBtnDown:
			{
				CPosition pt = pScene->ParentToSelf(msg.lParam , msg.wParam);
				pScene->OnLBtnDown(pt.X() , pt.Y());
				break;
			}
		case LBtnUp:
			{
				CPosition pt = pScene->ParentToSelf(msg.lParam , msg.wParam);
				pScene->OnLBtnUp(pt.X() , pt.Y());
				break;
			}
		case RBtnDown:
			{
				CPosition pt = pScene->ParentToSelf(msg.lParam , msg.wParam);
				pScene->OnRBtnDown(pt.X() , pt.Y());
				break;
			}
		case RBtnUp:
			{
				CPosition pt = pScene->ParentToSelf(msg.lParam , msg.wParam);
				pScene->OnRBtnUp(pt.X() , pt.Y());
				break;
			}
		case MouseMove:
			{
				CPosition pt = pScene->ParentToSelf(msg.lParam , msg.wParam);
				pScene->OnMouseMove(pt.X() , pt.Y());
				break;
			}
		case CharInput:
			pScene->OnInputChar((const wchar_t*)msg.lParam , msg.wParam);
			break;
		default:
			break;
		}
	}
}

void CUIWindow::OnDestroy()
{
	mSceneManager->OnDestroy();
}



