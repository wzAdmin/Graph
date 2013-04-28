#pragma once
#include "UILayer.h"
#include "gamedef.h"
#include "TimerManager.h"
class CGraphics;
class CBaseItem;
class CScoreCalculater;
class CGame : public CUILayer , public ITimerListener
{
	friend class CScoreCalculater;
	friend class CItem_2X1;
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CGame;}
	CGame(void);
	~CGame(void);
public:
	bool IsRun(){return m_IsRunning;}
private:
	virtual void DrawSelf(CGraphics* pGraphic);
	virtual void OnTimer(TimerID timeid);
	virtual bool OnKey(const KeyEvent& e);
	virtual void Load(const slim::XmlNode* node);
	unsigned int Goal();
	bool SigleFall();
	bool ConstructNewItem();
	bool m_IsRunning;
	unsigned int m_lastTime;
	CScoreCalculater *m_Calculater;
	GameState m_CurrentState;
	static const unsigned int s_ImageWidth = 32;
	static const unsigned int s_ImageHeight = 32;
	static const unsigned int s_ItemRowCount = 16;
	static const unsigned int s_ItemColunm = 8;
	
	ITEM m_Items[s_ItemColunm][s_ItemRowCount];
	CBaseItem* m_CurrentFallItem;
	TimerID mtimer;
};
