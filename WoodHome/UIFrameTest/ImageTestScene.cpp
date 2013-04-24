#include "ImageTestScene.h"
#include "UIButton.h"
#include "ImageBuffer.h"
#include "ImageResouceMgr.h"
#include "Transfrom.h"
#include "Graphics.h"
#include <Windows.h>
#include "Trace.h"
#include "UIFrame.h"

CImageTestScene::CImageTestScene(void):
mRotate(0.0f),
mSkewX(0.0f),
mSkewY(0.0f),
mScaleX(1.0f),
mScaleY(1.0f),
mtimeid(0)
{
}


CImageTestScene::~CImageTestScene(void)
{
	sUIFrame.GetTimerMgr()->RemoveTimer(mtimeid);
}

void CImageTestScene::Draw( CGraphics* pGraphic )
{
	CScene::Draw(pGraphic);
	CImageBuffer* pImage = sImageResource.GetImage(IMG_gril01);
	CTransfrom tf;
	tf.SetRotation(mRotate + mSkewX ,mRotate + mSkewY);
	tf.SetScale(mScaleX,mScaleY);
	tf.SetPosition(100,100);
	tf.Update();
	CBound bd = Bound();
	bd.Top(100);
	int a = GetTickCount();
	pGraphic->DrawImage(pImage,tf,NULL,&bd);
	DebugTrace(Trace_Info,"DrawTime:%d\n",GetTickCount() - a);
}

void CImageTestScene::Load( const slim::XmlNode* node )
{
	CScene::Load(node);
	CUIButton* pbtn = (CUIButton*)get("back");
	pbtn->AddClickListen(this,(OnBtnClick)&CImageTestScene::OnBtnbackClick);
	pbtn = (CUIButton*)get("ScaleX");
	pbtn->AddClickListen(this,(OnBtnClick)&CImageTestScene::OnBtnScaleXClick);
	pbtn = (CUIButton*)get("ScaleY");
	pbtn->AddClickListen(this,(OnBtnClick)&CImageTestScene::OnBtnScaleYClick);
	pbtn = (CUIButton*)get("SkewX");
	pbtn->AddClickListen(this,(OnBtnClick)&CImageTestScene::OnBtnSkewXClick);
	pbtn = (CUIButton*)get("SkewY");
	pbtn->AddClickListen(this,(OnBtnClick)&CImageTestScene::OnBtnSkewYClick);
	pbtn = (CUIButton*)get("Rotate");
	pbtn->AddClickListen(this,(OnBtnClick)&CImageTestScene::OnBtnRotateClick);
}

void CImageTestScene::OnBtnbackClick()
{
	Back();
}

void CImageTestScene::OnBtnScaleXClick()
{
	static float deltaX = 1.1f;
	if(mScaleX > 2.0f)
		deltaX= 0.9f;
	if(mScaleX < 0.3f)
		deltaX= 1.1f;
	mScaleX *= deltaX;
	DrawToWindow();
}

void CImageTestScene::OnBtnScaleYClick()
{
	static float deltaY = 1.1f;
	if(mScaleY > 2.0f)
		deltaY= 0.9f;
	if(mScaleY < 0.3f)
		deltaY= 1.1f;
	mScaleY *= deltaY;
	DrawToWindow();
}

void CImageTestScene::OnBtnRotateClick()
{
	mRotate += 10.0f * 3.1415926f / 180.0f;
	DrawToWindow();
}

void CImageTestScene::OnBtnSkewXClick()
{
	mSkewX += 10.0f * 3.1415926f / 180.0f;
	DrawToWindow();
}

void CImageTestScene::OnBtnSkewYClick()
{
	mSkewY += 10.0f * 3.1415926f / 180.0f;
	DrawToWindow();
}

void CImageTestScene::OnTimer( TimerID timerid )
{
	static float deltaX = 1.1f;
	if(mScaleX > 2.0f)
		deltaX= 0.9f;
	if(mScaleX < 0.3f)
		deltaX= 1.1f;
	mScaleX *= deltaX;
	DrawToWindow();
}

void CImageTestScene::OnHide()
{
	sUIFrame.GetTimerMgr()->RemoveTimer(mtimeid);
}

void CImageTestScene::OnShow( void* data /* = NULL */ )
{
	mtimeid =  sUIFrame.GetTimerMgr()->CreateTimer(this,20);
}
