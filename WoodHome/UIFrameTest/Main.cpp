#include "UIFrame.h"
#include "Trace.h"
//���ؿ���̨
//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
	DebugTrace("MainStarted\n");
	sUIFrame.StartWindow(Window_Main);
	return 0;
}