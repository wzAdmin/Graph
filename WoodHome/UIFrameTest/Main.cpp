#include "UIFrame.h"
#include "Trace.h"
#include "resource_image.h"
#include "FontConfig.h"
#include "FontEngine.h"
//Òþ²Ø¿ØÖÆÌ¨
//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
	DebugTrace(Trace_Normal,"MainStarted\n");
	sFontEngine.Init("msyh.ttf");
	sFontConfig.Load(USER_Font);
	sUIFrame.InitWindStyle(USER_WindowStyle);
	sUIFrame.StartWindow(Main_Window);
	sUIFrame.Run();
	sUIFrame.Destroy();
	sFontEngine.Destroy();
	Printmem();
	system("pause");
	return 0;
}