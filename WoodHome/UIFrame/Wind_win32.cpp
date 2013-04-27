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

CWind_win32::CWind_win32(Style_Window id) : CUIWindow(id)
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
	wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName	= L"window";
	wcex.hIconSm		= NULL;//LoadIcon(wcex.hInstance, L"_2_1.png");
	wcex.lpszMenuName   = NULL;
	RegisterClassEx(&wcex);
	mhWnd = CreateWindow(L"window", L"UI",WS_OVERLAPPED | \
		WS_CAPTION        | \
		WS_SYSMENU        | \
		WS_MINIMIZEBOX|WS_MINIMIZE,
		mPositionX,mPositionY, mWidth, mHeight, NULL, NULL, NULL, NULL);
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
	::SetWindowPos(mhWnd,HWND_TOP,mPositionX,mPositionY,mWidth,mHeight,SWP_SHOWWINDOW);
	::ShowWindow(mhWnd,SW_SHOWNORMAL);
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

void CWind_win32::DrawToWindow(const CBound* drawBound /*= NULL*/)
{
	HDC hdc = GetDC(mhWnd);
	DrawWin32(hdc,drawBound);
	DeleteDC(hdc);
}

LRESULT CALLBACK CWind_win32::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWind_win32* pwnd = (CWind_win32*)sUIFrame.GetWindow(WindID(hWnd));
	PAINTSTRUCT ps;
	HDC hdc;
	SystemMessage mss;
	switch (message)
	{
 	case WM_ERASEBKGND:
 		pwnd->DrawWin32(HDC(wParam));
 		return 0;
	case WM_PAINT:
		{
			hdc = ::BeginPaint(hWnd,&ps);
			::EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		sUIFrame.AddWindowToDelete(pwnd);
		if(sUIFrame.WndCount() < 1)
			sUIFrame.Exit();
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

void CWind_win32::DrawWin32( HDC hdc , const CBound* drawBound /*= NULL*/)
{
	if(mSceneManager->DrawScene(mGraphic , drawBound))
		BufferToWindow(mGraphic->GetImage());
}

void CWind_win32::Quit()
{
	::SendMessage(mhWnd ,WM_CLOSE,0,0);
}

void CWind_win32::Start()
{
	mSceneManager->GoTo(mStartSceneID);
	ShowWindow();
}

void CWind_win32::BufferToWindow( const CImageBuffer* buffer )
{
	HDC hdc= GetDC(mhWnd);
	BITHEADER header;
	header.mask[0] = 0xf800;
	header.mask[1] = 0x07e0;
	header.mask[2] = 0x001f;
	header.biBitCount = 16;
	header.biWidth = buffer->Width();
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biHeight = -buffer->Height();
	header.biPlanes = 1;
	header.biCompression = BI_BITFIELDS;
	header.biClrUsed = 0;
	header.biClrImportant = 0;
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	StretchDIBits(hdc, 0, 0, buffer->Width(),buffer->Height(), 0, 0,buffer->Width(),
		mFramebuffer->Height(),buffer->GetPixels(),(BITMAPINFO*)&header,0,SRCCOPY);
	DeleteDC(hdc);
}
