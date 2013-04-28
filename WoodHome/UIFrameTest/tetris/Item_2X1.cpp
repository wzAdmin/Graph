#include "Item_2X1.h"
#include "Game.h"

CItem_2X1::CItem_2X1(CGame* game):CBaseItem(game)
{
	m_position.X(3);
	m_position.Y(0);
	m_Self[0][0] = Int2ITEM((game->m_lastTime % 5) + 1);
	m_Self[1][0] = Int2ITEM(((game->m_lastTime+1) % 5) + 1);
	m_Self[0][1] = NOTHING;
	m_Self[1][1] = NOTHING;
	m_CurrentState = 0;
}


CItem_2X1::~CItem_2X1(void)
{
}

bool CItem_2X1::Fall()
{
	return SetPosition(CPosition(m_position.X(),m_position.Y() + 1));
}
void CItem_2X1::Change()
{
	ClearSelf();
	unsigned int old = m_CurrentState;
	ITEM oldItem[2][2];
	memcpy(oldItem,m_Self,sizeof(oldItem));
	switch(m_CurrentState)
	{
	case 0:
		m_CurrentState = 1;
		m_Self[0][1] = m_Self[0][0];
		m_Self[0][0] = m_Self[1][0];
		m_Self[1][0] = NOTHING;
		break;
	case 1:
		m_CurrentState = 2;
		m_Self[1][1] = m_Self[0][1];
		m_Self[0][1] = m_Self[0][0];
		m_Self[0][0] = NOTHING;
		break;
	case 2:
		m_CurrentState = 3;
		m_Self[1][0] = m_Self[1][1];
		m_Self[1][1] = m_Self[0][1];
		m_Self[0][1] = NOTHING;
		break;
	case 3:
		m_CurrentState = 0;
		m_Self[0][0] = m_Self[1][0];
		m_Self[1][0] = m_Self[1][1];
		m_Self[1][1] = NOTHING;
		break;
	default:
		break;
	}
	if(!Initialize())
	{
		m_CurrentState = old;
		memcpy(m_Self,oldItem,sizeof(oldItem));
		Initialize();
	}
}
void CItem_2X1::Left()
{
	SetPosition(CPosition(m_position.X() - 1,m_position.Y()));
}
void CItem_2X1::Right()
{
	SetPosition(CPosition(m_position.X() + 1,m_position.Y()));
}
bool CItem_2X1::Initialize()
{
	for(int i = 0; i < 2 ;i ++)
	{
		for(int j = 0; j < 2 ;j ++)
		{
			if(m_Self[i][j] != NOTHING)
			{
				if(i + m_position.X() < 0 || i + m_position.X()  > m_Game->s_ItemColunm -1 ||
					j + m_position.Y() < 0 || j + m_position.Y() > m_Game->s_ItemRowCount - 1)
					return false;
				if(m_Game->m_Items[i + m_position.X()][j + m_position.Y()] != NOTHING)
					return false;
			}
		}
	}
	for(int i = 0; i < 2 ;i ++)
	{
		for(int j = 0; j < 2 ;j ++)
		{
			if(i + m_position.X() < 0 || i + m_position.X()  > m_Game->s_ItemColunm -1 || 
				j + m_position.Y() < 0 || j + m_position.Y() > m_Game->s_ItemRowCount - 1)
				continue;
			if(m_Self[i][j] != NOTHING)
				m_Game->m_Items[i + m_position.X()][j + m_position.Y()] = m_Self[i][j];
		}
	}
	return true;
}

void CItem_2X1::ClearSelf()
{
	for(int i = 0; i < 2 ;i ++)
	{
		for(int j = 0; j < 2 ;j ++)
		{
			if(m_Self[i][j] != NOTHING)
				m_Game->m_Items[i + m_position.X()][j + m_position.Y()] = NOTHING;
		}
	}
}

bool CItem_2X1::SetPosition(const CPosition& position)
{
	ClearSelf();
	CPosition old = m_position;
	m_position = position;
	if(Initialize())
		return true;
	else
	{
		m_position = old;
		Initialize();
	}
	return false;
}