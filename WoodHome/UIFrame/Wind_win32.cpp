#include "Wind_win32.h"
#include "UIFrame.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "SceneManager.h"
#include "Scene.h"
struct BITHEADER : BITMAPINFOHEADER
{
	unsigned int mask[256];
};

CWind_win32::CWind_win32(Style_Window id) : CUIWindow(id)
{	
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
	mhWnd = CreateWindow(L"window", L"UI", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, NULL, NULL);
}


CWind_win32::~CWind_win32(void)
{
	if(mhWnd)
		::DestroyWindow(mhWnd);
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
	HDC hdc= GetWindowDC(mhWnd);
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
	ShowWindow();
	mSceneManager->GoTo(mStartSceneID);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK CWind_win32::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWind_win32* pwnd = (CWind_win32*)sUIFrame.GetWindow(WindID(hWnd));
	PAINTSTRUCT ps;
	HDC hdc;
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
		PostQuitMessage(0);
	case WM_MOUSEMOVE:
		break;
	case WM_IME_CHAR:
	case WM_IME_ENDCOMPOSITION:
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
