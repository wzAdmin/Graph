#include "UIFrame.h"
#include "Trace.h"
#include "resource_image.h"
#include "FontConfig.h"
//���ؿ���̨
//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
	DebugTrace("MainStarted\n");
	sFontConfig.Load(USER_Font);
	sUIFrame.InitWindStyle(USER_WindowStyle);
	sUIFrame.StartWindow(Main_Window);
	sUIFrame.Run();
	return 0;
}