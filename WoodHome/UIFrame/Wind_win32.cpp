#include "Wind_win32.h"
#include "UIFrame.h"
#include "ImageBuffer.h"
#include "Graphics.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Trace.h"


static KeyCode KeyMapping[0xff] = {
		KEYCODE_UNKNOWN, // 0x00, just a placeholder
		KEYCODE_UNKNOWN, // VK_LBUTTON        0x01
		KEYCODE_UNKNOWN, // VK_RBUTTON        0x02
		KEYCODE_UNKNOWN, // VK_CANCEL         0x03
		KEYCODE_UNKNOWN, // VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

		KEYCODE_UNKNOWN, // VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
		KEYCODE_UNKNOWN, // VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */


		KEYCODE_UNKNOWN, // unassigned        0x07

		KEYCODE_UNKNOWN, // VK_BACK           0x08
		KEYCODE_TAB,	 // VK_TAB            0x09

		KEYCODE_UNKNOWN, // reserved  0x0A
		KEYCODE_UNKNOWN, // reserved  0x0B

		KEYCODE_UNKNOWN, // VK_CLEAR          0x0C
		KEYCODE_ENTER, // VK_RETURN         0x0D

		KEYCODE_UNKNOWN, // reserved  0x0E
		KEYCODE_UNKNOWN, // reserved  0x0F

		KEYCODE_SHIFT_LEFT, // VK_SHIFT          0x10
		KEYCODE_UNKNOWN,    // VK_CONTROL        0x11
		KEYCODE_MENU,		// VK_MENU           0x12
		KEYCODE_MEDIA_PLAY_PAUSE, // VK_PAUSE          0x13
		KEYCODE_UNKNOWN,    // VK_CAPITAL        0x14

		KEYCODE_UNKNOWN, // VK_KANA VK_HANGEUL VK_HANGUL  0x15
		KEYCODE_UNKNOWN, // unassigned        0x16
		KEYCODE_UNKNOWN, // VK_JUNJA          0x17
		KEYCODE_UNKNOWN, // VK_FINAL          0x18
		KEYCODE_UNKNOWN, // VK_HANJA          0x19
		KEYCODE_UNKNOWN, // unassigned        0x1A

		KEYCODE_BACK,    // VK_ESCAPE         0x1B

		KEYCODE_UNKNOWN, // VK_CONVERT        0x1C
		KEYCODE_UNKNOWN, // VK_NONCONVERT     0x1D
		KEYCODE_UNKNOWN, // VK_ACCEPT         0x1E
		KEYCODE_UNKNOWN, // VK_MODECHANGE     0x1F

		KEYCODE_SPACE,   // VK_SPACE          0x20
		KEYCODE_UNKNOWN, // VK_PRIOR          0x21
		KEYCODE_UNKNOWN, // VK_NEXT           0x22
		KEYCODE_UNKNOWN, // VK_END            0x23
		KEYCODE_HOME,		// VK_HOME           0x24
		KEYCODE_DPAD_LEFT,	// VK_LEFT           0x25
		KEYCODE_DPAD_UP,	// VK_UP             0x26
		KEYCODE_DPAD_RIGHT, // VK_RIGHT          0x27
		KEYCODE_DPAD_DOWN,	// VK_DOWN           0x28
		KEYCODE_UNKNOWN, // VK_SELECT         0x29
		KEYCODE_UNKNOWN, // VK_PRINT          0x2A
		KEYCODE_UNKNOWN, // VK_EXECUTE        0x2B
		KEYCODE_UNKNOWN, // VK_SNAPSHOT       0x2C
		KEYCODE_UNKNOWN, // VK_INSERT         0x2D
		KEYCODE_DEL,	 // VK_DELETE         0x2E
		KEYCODE_UNKNOWN, // VK_HELP           0x2F

		// VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
		KEYCODE_0, // '0'  0x30
		KEYCODE_1, // '1'  0x31
		KEYCODE_2, // '2'  0x32
		KEYCODE_3, // '3'  0x33
		KEYCODE_4, // '4'  0x34
		KEYCODE_5, // '5'  0x35
		KEYCODE_6, // '6'  0x36
		KEYCODE_7, // '7'  0x37
		KEYCODE_8, // '8'  0x38
		KEYCODE_9, // '9'  0x39

		KEYCODE_UNKNOWN, // unassigned  0x3A
		KEYCODE_UNKNOWN, // unassigned  0x3B
		KEYCODE_UNKNOWN, // unassigned  0x3C
		KEYCODE_UNKNOWN, // unassigned  0x3D
		KEYCODE_UNKNOWN, // unassigned  0x3E
		KEYCODE_UNKNOWN, // unassigned  0x3F
		KEYCODE_UNKNOWN, // unassigned  0x40

		// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
		KEYCODE_A, // 'A'  0x41
		KEYCODE_B, // 'B'  0x42
		KEYCODE_C, // 'C'  0x43
		KEYCODE_D, // 'D'  0x44
		KEYCODE_E, // 'E'  0x45
		KEYCODE_F, // 'F'  0x46
		KEYCODE_G, // 'G'  0x47
		KEYCODE_H, // 'H'  0x48
		KEYCODE_I, // 'I'  0x49
		KEYCODE_J, // 'J'  0x4A
		KEYCODE_K, // 'K'  0x4B
		KEYCODE_L, // 'L'  0x4C
		KEYCODE_M, // 'M'  0x4D
		KEYCODE_N, // 'N'  0x4E
		KEYCODE_O, // 'O'  0x4F
		KEYCODE_P, // 'P'  0x50
		KEYCODE_Q, // 'Q'  0x51
		KEYCODE_R, // 'R'  0x52
		KEYCODE_S, // 'S'  0x53
		KEYCODE_T, // 'T'  0x54
		KEYCODE_U, // 'U'  0x55
		KEYCODE_V, // 'V'  0x56
		KEYCODE_W, // 'W'  0x57
		KEYCODE_X, // 'X'  0x58
		KEYCODE_Y, // 'Y'  0x59
		KEYCODE_Z, // 'Z'  0x5A

		KEYCODE_UNKNOWN, // VK_LWIN           0x5B
		KEYCODE_UNKNOWN, // VK_RWIN           0x5C
		KEYCODE_UNKNOWN, // VK_APPS           0x5D
		KEYCODE_UNKNOWN, // reserved          0x5E
		KEYCODE_UNKNOWN, // VK_SLEEP          0x5F

		KEYCODE_0, // VK_NUMPAD0        0x60
		KEYCODE_1, // VK_NUMPAD1        0x61
		KEYCODE_2, // VK_NUMPAD2        0x62
		KEYCODE_3, // VK_NUMPAD3        0x63
		KEYCODE_4, // VK_NUMPAD4        0x64
		KEYCODE_5, // VK_NUMPAD5        0x65
		KEYCODE_6, // VK_NUMPAD6        0x66
		KEYCODE_7, // VK_NUMPAD7        0x67
		KEYCODE_8, // VK_NUMPAD8        0x68
		KEYCODE_9, // VK_NUMPAD9        0x69
		KEYCODE_UNKNOWN, // VK_MULTIPLY       0x6A
		KEYCODE_UNKNOWN, // VK_ADD            0x6B
		KEYCODE_UNKNOWN, // VK_SEPARATOR      0x6C
		KEYCODE_MINUS,   // VK_SUBTRACT       0x6D
		KEYCODE_UNKNOWN, // VK_DECIMAL        0x6E
		KEYCODE_UNKNOWN, // VK_DIVIDE         0x6F
		KEYCODE_UNKNOWN, // VK_F1             0x70
		KEYCODE_UNKNOWN, // VK_F2             0x71
		KEYCODE_UNKNOWN, // VK_F3             0x72
		KEYCODE_UNKNOWN, // VK_F4             0x73
		KEYCODE_UNKNOWN, // VK_F5             0x74
		KEYCODE_UNKNOWN, // VK_F6             0x75
		KEYCODE_UNKNOWN, // VK_F7             0x76
		KEYCODE_UNKNOWN, // VK_F8             0x77
		KEYCODE_UNKNOWN, // VK_F9             0x78
		KEYCODE_UNKNOWN, // VK_F10            0x79
		KEYCODE_UNKNOWN, // VK_F11            0x7A
		KEYCODE_UNKNOWN, // VK_F12            0x7B
		KEYCODE_UNKNOWN, // VK_F13            0x7C
		KEYCODE_UNKNOWN, // VK_F14            0x7D
		KEYCODE_UNKNOWN, // VK_F15            0x7E
		KEYCODE_UNKNOWN, // VK_F16            0x7F
		KEYCODE_UNKNOWN, // VK_F17            0x80
		KEYCODE_UNKNOWN, // VK_F18            0x81
		KEYCODE_UNKNOWN, // VK_F19            0x82
		KEYCODE_UNKNOWN, // VK_F20            0x83
		KEYCODE_UNKNOWN, // VK_F21            0x84
		KEYCODE_UNKNOWN, // VK_F22            0x85
		KEYCODE_UNKNOWN, // VK_F23            0x86
		KEYCODE_UNKNOWN, // VK_F24            0x87

		/*
		 * 0x88 - 0x8F : unassigned
		 */
		KEYCODE_UNKNOWN, // unassigned        0x88
		KEYCODE_UNKNOWN, // unassigned        0x89
		KEYCODE_UNKNOWN, // unassigned        0x8A
		KEYCODE_UNKNOWN, // unassigned        0x8B
		KEYCODE_UNKNOWN, // unassigned        0x8C
		KEYCODE_UNKNOWN, // unassigned        0x8D
		KEYCODE_UNKNOWN, // unassigned        0x8E
		KEYCODE_UNKNOWN, // unassigned        0x8F

		KEYCODE_UNKNOWN, // VK_NUMLOCK        0x90
		KEYCODE_UNKNOWN, // VK_SCROLL         0x91

		/*
		 * NEC PC-9800 kbd definitions
		 */
		KEYCODE_UNKNOWN, // VK_OEM_NEC_EQUAL or VK_OEM_FJ_JISHO 0x92

		/*
		 * Fujitsu/OASYS kbd definitions
		 */
		KEYCODE_UNKNOWN, // VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
		KEYCODE_UNKNOWN, // VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
		KEYCODE_UNKNOWN, // VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
		KEYCODE_UNKNOWN, // VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

		/*
		 * 0x97 - 0x9F : unassigned
		 */
		KEYCODE_UNKNOWN, // unassigned        0x97
		KEYCODE_UNKNOWN, // unassigned        0x98
		KEYCODE_UNKNOWN, // unassigned        0x99
		KEYCODE_UNKNOWN, // unassigned        0x9A
		KEYCODE_UNKNOWN, // unassigned        0x9B
		KEYCODE_UNKNOWN, // unassigned        0x9C
		KEYCODE_UNKNOWN, // unassigned        0x9D
		KEYCODE_UNKNOWN, // unassigned        0x9E
		KEYCODE_UNKNOWN, // unassigned        0x9F

		/*
		 * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
		 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
		 * No other API or message will distinguish left and right keys in this way.
		 */
		KEYCODE_SHIFT_LEFT, // VK_LSHIFT         0xA0
		KEYCODE_SHIFT_RIGHT,// VK_RSHIFT         0xA1
		KEYCODE_UNKNOWN,	// VK_LCONTROL       0xA2
		KEYCODE_UNKNOWN,	// VK_RCONTROL       0xA3
		KEYCODE_UNKNOWN,	// VK_LMENU          0xA4
		KEYCODE_UNKNOWN,	// VK_RMENU          0xA5

		KEYCODE_UNKNOWN, // VK_BROWSER_BACK        0xA6
		KEYCODE_UNKNOWN, // VK_BROWSER_FORWARD     0xA7
		KEYCODE_UNKNOWN, // VK_BROWSER_REFRESH     0xA8
		KEYCODE_UNKNOWN, // VK_BROWSER_STOP        0xA9
		KEYCODE_UNKNOWN, // VK_BROWSER_SEARCH      0xAA
		KEYCODE_UNKNOWN, // VK_BROWSER_FAVORITES   0xAB
		KEYCODE_UNKNOWN, // VK_BROWSER_HOME        0xAC

		KEYCODE_MUTE,		// VK_VOLUME_MUTE         0xAD
		KEYCODE_VOLUME_DOWN,// VK_VOLUME_DOWN         0xAE
		KEYCODE_VOLUME_UP,  // VK_VOLUME_UP           0xAF
		KEYCODE_MEDIA_NEXT, // VK_MEDIA_NEXT_TRACK    0xB0
		KEYCODE_MEDIA_PREVIOUS, // VK_MEDIA_PREV_TRACK    0xB1
		KEYCODE_MEDIA_STOP, // VK_MEDIA_STOP          0xB2
		KEYCODE_MEDIA_PLAY_PAUSE, // VK_MEDIA_PLAY_PAUSE    0xB3
		KEYCODE_UNKNOWN, // VK_LAUNCH_MAIL         0xB4
		KEYCODE_UNKNOWN, // VK_LAUNCH_MEDIA_SELECT 0xB5
		KEYCODE_UNKNOWN, // VK_LAUNCH_APP1         0xB6
		KEYCODE_UNKNOWN, // VK_LAUNCH_APP2         0xB7

		/*
		 * 0xB8 - 0xB9 : reserved
		 */
		KEYCODE_UNKNOWN, // reserved  0xB8
		KEYCODE_UNKNOWN, // reserved  0xB9

		KEYCODE_UNKNOWN, // VK_OEM_1          0xBA   // ';:' for US
		KEYCODE_UNKNOWN, // VK_OEM_PLUS       0xBB   // '+' any country
		KEYCODE_UNKNOWN, // VK_OEM_COMMA      0xBC   // ',' any country
		KEYCODE_UNKNOWN, // VK_OEM_MINUS      0xBD   // '-' any country
		KEYCODE_UNKNOWN, // VK_OEM_PERIOD     0xBE   // '.' any country
		KEYCODE_UNKNOWN, // VK_OEM_2          0xBF   // '/?' for US
		KEYCODE_UNKNOWN, // VK_OEM_3          0xC0   // '`~' for US

		/*
		 * 0xC1 - 0xD7 : reserved
		 */
		KEYCODE_UNKNOWN, // reserved  0xC1
		KEYCODE_UNKNOWN, // reserved  0xC2
		KEYCODE_UNKNOWN, // reserved  0xC3
		KEYCODE_UNKNOWN, // reserved  0xC4
		KEYCODE_UNKNOWN, // reserved  0xC5
		KEYCODE_UNKNOWN, // reserved  0xC6
		KEYCODE_UNKNOWN, // reserved  0xC7
		KEYCODE_UNKNOWN, // reserved  0xC8
		KEYCODE_UNKNOWN, // reserved  0xC9
		KEYCODE_UNKNOWN, // reserved  0xCA
		KEYCODE_UNKNOWN, // reserved  0xCB
		KEYCODE_UNKNOWN, // reserved  0xCC
		KEYCODE_UNKNOWN, // reserved  0xCD
		KEYCODE_UNKNOWN, // reserved  0xCE
		KEYCODE_UNKNOWN, // reserved  0xCF
		KEYCODE_UNKNOWN, // reserved  0xD0
		KEYCODE_UNKNOWN, // reserved  0xD1
		KEYCODE_UNKNOWN, // reserved  0xD2
		KEYCODE_UNKNOWN, // reserved  0xD3
		KEYCODE_UNKNOWN, // reserved  0xD4
		KEYCODE_UNKNOWN, // reserved  0xD5
		KEYCODE_UNKNOWN, // reserved  0xD6
		KEYCODE_UNKNOWN, // reserved  0xD7

		/*
		 * 0xD8 - 0xDA : unassigned
		 */
		KEYCODE_UNKNOWN, // unassigned  0xD8
		KEYCODE_UNKNOWN, // unassigned  0xD9
		KEYCODE_UNKNOWN, // unassigned  0xDA

		KEYCODE_UNKNOWN, // VK_OEM_4          0xDB  //  '[{' for US
		KEYCODE_UNKNOWN, // VK_OEM_5          0xDC  //  '\|' for US
		KEYCODE_UNKNOWN, // VK_OEM_6          0xDD  //  ']}' for US
		KEYCODE_UNKNOWN, // VK_OEM_7          0xDE  //  ''"' for US
		KEYCODE_UNKNOWN, // VK_OEM_8          0xDF

		/*
		 * 0xE0 : reserved
		 */
		KEYCODE_UNKNOWN, // reserved  0xE0

		/*
		 * Various extended or enhanced keyboards
		 */
		KEYCODE_UNKNOWN, // VK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
		KEYCODE_UNKNOWN, // VK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
		KEYCODE_UNKNOWN, // VK_ICO_HELP       0xE3  //  Help key on ICO
		KEYCODE_UNKNOWN, // VK_ICO_00         0xE4  //  00 key on ICO
		KEYCODE_UNKNOWN, // VK_PROCESSKEY     0xE5
		KEYCODE_UNKNOWN, // VK_ICO_CLEAR      0xE6
		KEYCODE_UNKNOWN, // VK_PACKET         0xE7

		KEYCODE_UNKNOWN, // unassigned  0xE8

		/*
		 * Nokia/Ericsson definitions
		 */
		KEYCODE_UNKNOWN, // VK_OEM_RESET      0xE9
		KEYCODE_UNKNOWN, // VK_OEM_JUMP       0xEA
		KEYCODE_UNKNOWN, // VK_OEM_PA1        0xEB
		KEYCODE_UNKNOWN, // VK_OEM_PA2        0xEC
		KEYCODE_UNKNOWN, // VK_OEM_PA3        0xED
		KEYCODE_UNKNOWN, // VK_OEM_WSCTRL     0xEE
		KEYCODE_UNKNOWN, // VK_OEM_CUSEL      0xEF
		KEYCODE_UNKNOWN, // VK_OEM_ATTN       0xF0
		KEYCODE_UNKNOWN, // VK_OEM_FINISH     0xF1
		KEYCODE_UNKNOWN, // VK_OEM_COPY       0xF2
		KEYCODE_UNKNOWN, // VK_OEM_AUTO       0xF3
		KEYCODE_UNKNOWN, // VK_OEM_ENLW       0xF4
		KEYCODE_UNKNOWN, // VK_OEM_BACKTAB    0xF5

		KEYCODE_UNKNOWN, // VK_ATTN           0xF6
		KEYCODE_UNKNOWN, // VK_CRSEL          0xF7
		KEYCODE_UNKNOWN, // VK_EXSEL          0xF8
		KEYCODE_UNKNOWN, // VK_EREOF          0xF9
		KEYCODE_UNKNOWN, // VK_PLAY           0xFA
		KEYCODE_UNKNOWN, // VK_ZOOM           0xFB
		KEYCODE_UNKNOWN, // VK_NONAME         0xFC
		KEYCODE_UNKNOWN, // VK_PA1            0xFD
		KEYCODE_UNKNOWN, // VK_OEM_CLEAR      0xFE
};


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
	case WM_CHAR:
		pwnd->mInputCount = 1;
		pwnd->mInputChar[0] = wchar_t(wParam & 0xffff);
		mss.msg = CharInput;
		mss.wParam = pwnd->mInputCount;
		mss.lParam = int(pwnd->mInputChar);
		pwnd->DispatchSysMessage(mss);
		pwnd->mInputCount = 0;
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		mss.msg = Key;
		mss.wParam = KeyMapping[wParam];
		GetKeyboardState(pwnd->mAllkeystatus);
		mss.lParam = ((WM_KEYDOWN == message)<<2) | 
			((pwnd->mAllkeystatus[VK_SHIFT]>>7)<<1) |
				(pwnd->mAllkeystatus[VK_CONTROL]>>7);
		pwnd->DispatchSysMessage(mss);
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

void CWind_win32::SetIMEPos( int x , int y )
{
	HIMC imc = ImmGetContext(mhWnd);
	COMPOSITIONFORM cddf;
	ImmGetCompositionWindow(imc ,&cddf);
	cddf.dwStyle = CFS_CANDIDATEPOS;
	cddf.ptCurrentPos.x = x;
	cddf.ptCurrentPos.y = y;
	ImmSetCompositionWindow(imc,&cddf);
}
