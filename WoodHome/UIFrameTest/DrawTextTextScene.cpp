#include "DrawTextTextScene.h"
#include "UIButton.h"
#include "Graphics.h"
#include "FontConfig.h"
#include "Trace.h"

CDrawTextTextScene::CDrawTextTextScene(void)
{
}


CDrawTextTextScene::~CDrawTextTextScene(void)
{
}

void CDrawTextTextScene::Draw( CGraphics* pGraphic )
{
	CScene::Draw(pGraphic);
	pGraphic->DrawTextW(L"吴德宏",100,300,*sFontConfig.GetFont(3));	
	CPosition pts[5];
	pts[4] = CPosition(800,900);
	pts[3] = CPosition(600,500);
	pts[2] = CPosition(200,600);
	pts[1] = CPosition(200,300);
	pts[0] = CPosition(30,200);
	int a = GetTickCount();
	pGraphic->Polygon(pts,5,CRGB(255,124,122));
	DebugTrace(Trace_Info,"Polygon Time:%d\n",GetTickCount() - a);
	wchar_t* wcs = L"这是沿线绘制吴德宏啊伍德WoodHome";
	pGraphic->DrawTextW(wcs,pts,5,*sFontConfig.GetFont(2),50.0f);
	pGraphic->LineDDA(pts[0],pts[1],0,CRGB(255,124,122));
	pGraphic->LineDDA(pts[1],pts[2],0,CRGB(255,124,122));
	pGraphic->LineDDA(pts[2],pts[3],0,CRGB(255,124,122));
	pGraphic->LineDDA(pts[3],pts[4],0,CRGB(255,124,122));
	pts[0]=CPosition(600,20);
	pts[1]=CPosition(800,550);
	pGraphic->LineDDA(pts[0], 20 ,pts[1] ,10,CRGB(124,124,122));
	a = GetTickCount();
	pGraphic->DrawTextW(L"这是不等宽线",pts,2,*sFontConfig.GetFont(1),20);
	DebugTrace(Trace_Info,"不等宽线 Time:%d\n",GetTickCount() - a);
	pts[1]=CPosition(700,20);
	pts[0]=CPosition(200,120);
	a = GetTickCount();
	pGraphic->LineDDA(pts[0] ,pts[1] ,15,CRGB(124,124,122));
	pGraphic->DrawTextW(L"这是等宽线",pts,2,*sFontConfig.GetFont(1),20);
	DebugTrace(Trace_Info,"等宽线 Time:%d\n",GetTickCount() - a);
}


void CDrawTextTextScene::OnBtnbackClick()
{
	Back();
}

void CDrawTextTextScene::OnLoad()
{
	CUIButton* back = (CUIButton*)get("back");
	back->AddClickListen(this,(OnBtnClick)&CDrawTextTextScene::OnBtnbackClick);
}
