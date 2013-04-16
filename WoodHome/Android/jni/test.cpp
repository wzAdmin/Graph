#include <jni.h>
#include <android/bitmap.h>
#include "Graphics.h"
#include "PtAlongLine.h"
 extern "C" void Java_com_Wood_Home_HomeView_test( JNIEnv* env,
	jobject thiz ,jobject jbitmap)
{
	CImageBuffer buffer;
	buffer.Initialize(480,800,false);
	buffer.ClearColor(CRGB(255,222,0));
	CGraphics g(&buffer);
	g.LineDDA(CPosition(100,20), 20 , CPosition(300,550),10,CRGB(124,124,122));
	Font ft;
	ft.color = CRGB(100,100,0);
	ft.width=16;
	ft.height=16;
	g.DrawTextW(L"吴德宏_WoodHome!!",200,400,ft);
	CPtAlongLine aline;
	CPosition pts[4];
	pts[3] = CPosition(600,500);
	pts[2] = CPosition(200,200);
	pts[1] = CPosition(100,100);
	pts[0] = CPosition(0,0);
	 while(aline.Next())
	 {
	 	g.DrawTextW(L"吴",aline.X(),aline.Y(),ft);
	 }
	void* pixels = 0;
	AndroidBitmap_lockPixels(env,jbitmap,&pixels);
	memcpy(pixels,g.GetImage()->GetPixels(),g.Stride()*g.Height()*2);
	AndroidBitmap_unlockPixels(env,jbitmap);
}