#include "BaseItem.h"


CBaseItem::CBaseItem(CGame* game)
{
	m_Game = game;
}


CBaseItem::~CBaseItem(void)
{
}

ITEM CBaseItem::Int2ITEM(unsigned int val)
{
	switch(val)
	{
	case 1:
		return BLACK;
	case 2:
		return WHITE;
	case 3:
		return RED;
	case 4:
		return YELLOW;
	case 5:
		return GREEN;
	default:
		return BLACK;
	}
}