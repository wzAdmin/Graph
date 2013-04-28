#include "Game.h"
#include "BaseItem.h"
#include "ItemFactroy.h"
#include "ScoreCalculater.h"
#include "Bound.h"
#include "ImageBuffer.h"
#include "ImageResouceMgr.h"
#include "Graphics.h"
#include "Scene.h"
#include "UIFrame.h"
#include <Windows.h>


CGame::CGame(void)
{
	mtimer = InvalidTimer;
	m_IsRunning = true;
	m_CurrentState = BEGIN;
	memset(m_Items,0,sizeof(m_Items));
	m_lastTime = 0;
	m_CurrentFallItem = 0;
	m_Calculater = new CScoreCalculater(this);
}


CGame::~CGame(void)
{
	delete m_Calculater;
	m_Calculater = 0;
}

void CGame::DrawSelf(CGraphics* pGraphic)
{
	if( InvalidTimer == mtimer)
	{
		mtimer = sUIFrame.GetTimerMgr()->CreateTimer(this,50);
	}
	CImageBuffer* pimage = NULL;
	for(unsigned int i = 0; i < s_ItemColunm ; i ++)
	{
		for(unsigned int j = 0; j < s_ItemRowCount ; j ++)
		{
			CBound dstbd(i*s_ImageWidth,(i+1)*s_ImageWidth -1 ,
				j*s_ImageHeight ,(j + 1)*s_ImageHeight );
			switch(m_Items[i][j])
			{
			case NOTHING:
				break;
			case WHITE:
				{
					pimage = sImageResource.GetImage(IMG_white);
				}
				break;
			case BLACK:
				{
					pimage = sImageResource.GetImage(IMG_black);
				}
				break;
			case RED:
				{
					pimage = sImageResource.GetImage(IMG_red);
				}
				break;
			case YELLOW:
				{
					pimage = sImageResource.GetImage(IMG_yellow);
				}
				break;
			case GREEN:
				{
					pimage = sImageResource.GetImage(IMG_green);
				}
				break;
			default:
				break;
			}
			this->Absolute(dstbd);
			if(NOTHING == m_Items[i][j])
				pGraphic->FillBoud(dstbd,CRGB(0,0,0));
			else
				pGraphic->DrawImage_Repeat(pimage,&dstbd);
		}
	}
}

void CGame::OnTimer(TimerID timeid)
{
	if(!IsRealVisible())
	{
		sUIFrame.GetTimerMgr()->RemoveTimer(mtimer);
		mtimer = InvalidTimer;
		return;
	}
	unsigned int time = GetTickCount();
	switch(m_CurrentState)
	{
	case BEGIN:
		m_CurrentState = CONSTRUCT;
		m_lastTime = time;
		break;
	case CONSTRUCT:
		if(!ConstructNewItem())
			m_CurrentState = END;
		else
			m_CurrentState = FALLING;
		break;
	case FALLING:
		if(time - m_lastTime > 1000)
		{
			if(!m_CurrentFallItem->Fall())
				m_CurrentState = FALLED;
			m_lastTime = time;
		}
		break;
	case SIGLEFALLING:		
		if(time - m_lastTime > 100)
		{
			if(!SigleFall())
			{
				unsigned int score = m_Calculater->Calculate();
				if(-1 == score)
					m_CurrentState = CONSTRUCT;
			}
			m_lastTime = time;
		}
		break;
	case FALLED:
		m_CurrentState = SIGLEFALLING;
		break;
	case END:
		m_IsRunning = false;
		break;
	default:
		break;
	}
	DrawToWindow();
}

bool CGame::SigleFall()
{
	bool re = false;
	for(int i = 0 ; i < s_ItemColunm ; i ++)
	{
		for(int j = s_ItemRowCount - 1; j > 0 ; j --)
		{
			if(NOTHING == m_Items[i][j] && NOTHING!=m_Items[i][j-1])
			{
				re = true;
				m_Items[i][j] = m_Items[i][j-1];
				m_Items[i][j-1] = NOTHING;
			}
		}
	}
	return re;
}

unsigned int Goal()
{
	return 0;
}
bool CGame::ConstructNewItem()
{
	m_CurrentFallItem = CItemFactroy::Instance().CreateItem(this);
	return m_CurrentFallItem !=0;
}

bool CGame::OnKey( const KeyEvent& e )
{
	if(!m_CurrentFallItem)
		return true;
	if(e.isDown)
	{
		switch(e.key)
		{
		case KEYCODE_DPAD_LEFT:
			m_CurrentFallItem->Left();
			break;
		case KEYCODE_DPAD_RIGHT:
			m_CurrentFallItem->Right();
			break;
		case KEYCODE_DPAD_UP:
			m_CurrentFallItem->Change();
			break;
		case KEYCODE_DPAD_DOWN:
			m_CurrentFallItem->Fall();
			break;
		}
	}
	return true;
}


void CGame::Load( const slim::XmlNode* node )
{
	CUILayer::Load(node);
	mtimer = sUIFrame.GetTimerMgr()->CreateTimer(this,50);
}
