#include "Wind_win32.h"
#include "UIFrame.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Trace.h"
struct BITHEADER : BITMAPINFOHEADER
{
	unsigned int mask[256];
};

CWind_win32::CWind_win32(Style_Window id) : CUIWindow(id),mbDestroyed(false)
{
	mInputCount = 0;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= NULL;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName	= L"window";
	wcex.hIconSm		= NULL;//LoadIcon(wcex.hInstance, L"_2_1.png");
	wcex.lpszMenuName   = NULL;
	RegisterClassEx(&wcex);
	int y =GetSystemMetrics(SM_CYCAPTION);
	mhWnd = CreateWindow(L"window", L"UI",
		WS_OVERLAPPEDWINDOW,
		0,0, mWidth, mHeight, NULL, NULL, NULL, NULL);
}


CWind_win32::~CWind_win32(void)
{
}

void CWind_win32::MessageTo( WindID windowId,const SystemMessage& msg )
{
	CWind_win32* pwind = static_cast<CWind_win32*>(sUIFrame.GetWindow(windowId));
	if(pwind)
		::SendMessage(pwind->mhWnd , msg.msg , msg.wParam , msg.lParam);
}

void CWind_win32::ShowWindow()
{
	::ShowWindow(mhWnd,SW_SHOW);
}

void CWind_win32::HideWindow()
{
	::ShowWindow(mhWnd,SW_HIDE);
}

void CWind_win32::Minimize()
{
	::ShowWindow(mhWnd,SW_MINIMIZE);
}

void CWind_win32::SetPostion( int x , int y )
{

}

void CWind_win32::DrawToWindow()
{
	mSceneManager->GetCurScene()->Draw(mGraphic);
	HDC hdc= GetDC(mhWnd);
	BITHEADER header;
	header.mask[0] = 0xf800;
	header.mask[1] = 0x07e0;
	header.mask[2] = 0x001f;
	header.biBitCount = 16;
	header.biWidth = mFramebuffer->Width();
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biHeight = -mFramebuffer->Height();
	header.biPlanes = 1;
	header.biCompression = BI_BITFIELDS;
	header.biClrUsed = 0;
	header.biClrImportant = 0;
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	StretchDIBits(hdc, 0, 0, mFramebuffer->Width(),mFramebuffer->Height(), 0, 0,mFramebuffer->Width(),
		mFramebuffer->Height(),mFramebuffer->GetPixels(),(BITMAPINFO*)&header,0,SRCCOPY);
	DeleteDC(hdc);
}

void CWind_win32::Run()
{
	MSG msg;
	mSceneManager->GoTo(mStartSceneID);
	ShowWindow();
	while (GetMessage(&msg, NULL, 0, 0))
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK CWind_win32::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWind_win32* pwnd = (CWind_win32*)sUIFrame.GetWindow(WindID(hWnd));
	if(pwnd && pwnd->mbDestroyed)
		DebugTrace("ERROR\n");
	PAINTSTRUCT ps;
	HDC hdc;
	SystemMessage mss;
	switch (message)
	{
	case WM_PAINT:
		{
			hdc = ::BeginPaint(hWnd,&ps);
			pwnd->DrawWin32(hdc);
			::EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		if(!pwnd)
			DebugTrace("WM_DESTROY NULL WND!");
		if(pwnd &&pwnd->mbDestroyed)
			DebugTrace("WM_DESTROY TWICE");
		if(pwnd)
		{
			pwnd->mbDestroyed = true;
			sUIFrame.DestroyWnd(pwnd);
		}
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		mss.msg = MouseMove;
		mss.lParam = LOWORD(lParam);
		mss.wParam = HIWORD(lParam);
		pwnd->DispatchSysMessage(mss);
		break;
	case WM_LBUTTONUP:
		mss.msg = LBtnUp;
		mss.lParam = LOWORD(lParam);
		mss.wParam = HIWORD(lParam);
		pwnd->DispatchSysMessage(mss);
		break;
	case WM_LBUTTONDOWN:
		mss.msg = LBtnDown;
		mss.lParam = LOWORD(lParam);
		mss.wParam = HIWORD(lParam);
		pwnd->DispatchSysMessage(mss);
		break;
	case WM_RBUTTONUP:
		mss.msg = RBtnUp;
		mss.lParam = LOWORD(lParam);
		mss.wParam = HIWORD(lParam);
		pwnd->DispatchSysMessage(mss);
		break;
	case WM_RBUTTONDOWN:
		mss.msg = RBtnDown;
		mss.lParam = LOWORD(lParam);
		mss.wParam = HIWORD(lParam);
		pwnd->DispatchSysMessage(mss);
		break;
	case WM_IME_CHAR:
		pwnd->mInputChar[pwnd->mInputCount++] = wchar_t(wParam&0xffff);
		break;
	case WM_IME_ENDCOMPOSITION:
		{
			mss.msg = CharInput;
			mss.wParam = pwnd->mInputCount;
			mss.lParam = int(pwnd->mInputChar);
			pwnd->DispatchSysMessage(mss);
			pwnd->mInputCount = 0;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CWind_win32::DrawWin32( HDC hdc )
{
	mSceneManager->GetCurScene()->Draw(mGraphic);
	BITHEADER header;
	header.mask[0] = 0xf800;
	header.mask[1] = 0x07e0;
	header.mask[2] = 0x001f;
	header.biBitCount = 16;
	header.biWidth = mFramebuffer->Width();
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biHeight = -mFramebuffer->Height();
	header.biPlanes = 1;
	header.biCompression = BI_BITFIELDS;
	header.biClrUsed = 0;
	header.biClrImportant = 0;
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	StretchDIBits(hdc, 0, 0, mFramebuffer->Width(),mFramebuffer->Height(), 0, 0,mFramebuffer->Width(),
		mFramebuffer->Height(),mFramebuffer->GetPixels(),(BITMAPINFO*)&header,0,SRCCOPY);
}

void CWind_win32::Quit()
{
	PostMessage(mhWnd ,WM_CLOSE,0,0);
}
