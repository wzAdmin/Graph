#include "SceneManager.h"
#include "Scene.h"
#include "FileSystem.h"
#include "SlimXml.h"
#include "UIFrame.h"
#include "UIObjectFactory.h"
#include "Memory_Check.h"
#include "Graphics.h"
#include "EffectFactory.h"

CSceneManager::CSceneManager(CUIWindow* wnd):mWind(wnd),mEffect(NULL),mCurDialog(NULL)
{
}


CSceneManager::~CSceneManager(void)
{
	SceneMapItor it = mScenes.begin();
	for ( ; mScenes.end() != it ; it++)
	{
		DELETE_LEAKCHECK(it->second);
	}
	if(mEffect)
		DELETE_LEAKCHECK(mEffect);
}

void CSceneManager::GoTo( SourceID toid ,CScene* from /*= 0*/ ,void* data/* = NULL*/, EffectType effect /*= Effect_Invalid*/)
{
	mParam_Onshow = data;
	// hide from
	if(from)
	{
		from->Visible(false);
		from->OnHide();
		from->Notify();
	}
	SceneMapItor it = mScenes.find(toid);
	CScene* pTo = NULL;

	//created already
	if(mScenes.end() != it)
	{

		SceneListItor itor = mSceneStack.begin();
		for( ; mSceneStack.end() != itor && (*itor) != it->second ; itor++);
		if(mSceneStack.end() != itor)
			mSceneStack.erase(itor);
		pTo = it->second;
		mSceneStack.push_back(pTo);
	}
	else// has not created so create a new
	{
		pTo = CreatScene(toid);
		mScenes.insert(std::pair<SourceID,CScene*>(toid,pTo));
		pTo->Visible(false);
		mSceneStack.push_back(pTo);
	}

	//no effect
	if(!from || Effect_Invalid == effect)
	{
		pTo->Visible(true);
		pTo->OnShow(mParam_Onshow);
		pTo->DrawToWindow();
	}
	else//deal effect
	{
		mEffect = sUIFrame.GetEffectFactory()->CreateEffect(effect,this,50,10,mWind->Graphic());
		mEffect->Start(from , pTo);
	}
}

CScene* CSceneManager::GetCurScene()
{
	assert(!mSceneStack.empty());
	return mSceneStack.back();
}

CScene* CSceneManager::CreatScene( SourceID sceneid )
{
	//load data
	Sourceitem item = sFilesystem.GetSource(sceneid);
	char* pdata = NEW_LEAKCHECK char[item.length];
	sFilesystem.LoadSource(item,pdata);

	//load xml
	slim::XmlDocument doc;
	doc.loadFromMemory(pdata,item.length);
	DELETEARR_LEAKCHECK(pdata);

	// parse the scene
	slim::NodeIterator nodeit ;
	slim::XmlNode* child = doc.getFirstChild(nodeit);
	CScene* pScene = (CScene*)sUIFrame.GetObjFactory()->CreateObject(child->getName());
	pScene->Load(child);
	pScene->SetWind(mWind);
	return pScene;
}

void CSceneManager::Back(void* data /*= NULL*/, EffectType effect /*= Effect_Invalid*/)
{
	mParam_Onshow = data;
	if(1==mSceneStack.size())
		printf("left scene < 2 can not Back\n");
	else
	{
		CScene* pcur = mSceneStack.back();
		pcur->Visible(false);
		pcur->OnHide();
		mSceneStack.pop_back();
		//deal effect
		if(Effect_Invalid != effect)
		{
			mEffect = sUIFrame.GetEffectFactory()->CreateEffect(effect,this,50,20,mWind->Graphic());
			mEffect->Start(pcur , mSceneStack.back());
		}
		else
		{
			mSceneStack.back()->Visible(true);
			mSceneStack.back()->OnShow(mParam_Onshow);
			mSceneStack.back()->DrawToWindow();
		}
	}
}

void CSceneManager::OnDestroy()
{
	SceneMapItor it = mScenes.begin();
	for ( ; mScenes.end() != it ; it++)
	{
		it->second->OnUnload();
	}
}

void CSceneManager::OnEffect()
{
	mWind->BufferToWindow(mWind->Graphic()->GetImage());
}

void CSceneManager::OnEffectEnd( CScene* src , CScene* dest )
{
	dest->Visible(true);
	dest->OnShow(mParam_Onshow);
	dest->DrawToWindow();
	DELETE_LEAKCHECK(mEffect);
	mEffect = NULL;
}

bool CSceneManager::DrawScene( CGraphics* pGraphic , const CBound* drawBound /*= NULL*/ )
{
	if(!GetCurScene()->Visible())
		return false;
	pGraphic->SetClipBound(0,0,pGraphic->Width() - 1,pGraphic->Height() - 1);
	if(drawBound)
		pGraphic->SetClipBound(*drawBound);
	GetCurScene()->Draw(pGraphic);

	//
	//if have a dialog darken current scene and draw dialog
	//
	if(mCurDialog && mCurDialog->Visible())
	{
		CImageBuffer buffer;
		buffer.Initialize(1,1,false);
		buffer.ClearColor(CRGB(0,0,0));
		CBound bd = pGraphic->GetClipBound();
		pGraphic->DrawImage_Repeat(&buffer,unsigned char(15),&bd);
		mCurDialog->Draw(pGraphic);
	}
	return true;
}

void CSceneManager::GotoAsDialog( SourceID sceneid , void* data /*= NULL*/ )
{
	SceneMapItor it = mScenes.find(sceneid);
	if(mScenes.end() == it)
	{
		mCurDialog = CreatScene(sceneid);
		mScenes.insert(std::pair<SourceID,CScene*>(sceneid,mCurDialog));
	}
	else
		mCurDialog = it->second;
	mCurDialog->Visible(true);
	mCurDialog->OnShow(data);

	//Set dialog's position to the center
	CScene* pcur = GetCurScene();
	const CBound& bd = pcur->Bound();
	int centerX = (bd.Left() + bd.Right()) / 2;
	int centerY = (bd.Top() + bd.Bottom()) / 2;
	CBound dstbd = mCurDialog->Bound();
	int cx = (dstbd.Left() + dstbd.Right()) / 2;
	int cy = (dstbd.Top() + dstbd.Bottom()) / 2;
	dstbd.Move(centerX - cx , centerY -cy);
	mCurDialog->Bound(dstbd);

	mWind->DrawToWindow();
}

CScene* CSceneManager::GetCurMsgScene()
{
	if(mCurDialog && mCurDialog->Visible())
		return mCurDialog;
	return GetCurScene();
}
