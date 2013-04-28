#pragma once
#include "Position.h"
#include "baseitem.h"
//   -------
//  |       |
//  |       |
//   -------
//  |       |
//  |       |
//   -------

class CItem_2X1 :
	public CBaseItem
{
public:
	CItem_2X1(CGame* game);
	~CItem_2X1(void);
private:
	virtual bool Fall();
	virtual void Change();
	virtual void Left();
	virtual void Right(); 
	virtual bool Initialize();
	bool SetPosition(const CPosition& position);
	void ClearSelf();
private:
	ITEM m_Self[2][2];
	CPosition m_position;
	unsigned int m_CurrentState;
};

