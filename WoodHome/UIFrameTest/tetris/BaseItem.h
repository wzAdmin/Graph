#pragma once
class CGame;
#include"gamedef.h"
class CBaseItem
{
public:
	CBaseItem(CGame* game);
	virtual ~CBaseItem(void);
public:
	virtual bool Fall() = 0;
	virtual void Change() = 0;
	virtual void Left() = 0;
	virtual void Right() = 0;
	virtual bool Initialize() = 0;
protected:
	ITEM Int2ITEM(unsigned int val);
	CGame* m_Game;
};

