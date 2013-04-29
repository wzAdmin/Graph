#include "ItemFactroy.h"
#include "Item_2X1.h"
#include "Memory_Check.h"

CItemFactroy::CItemFactroy(void)
{
}


CItemFactroy::~CItemFactroy(void)
{
}

CBaseItem* CItemFactroy::CreateItem(CGame* game)
{
	CBaseItem* item = NEW_LEAKCHECK CItem_2X1(game);
	if(item->Initialize())
		return item;
	else
		DELETE_LEAKCHECK(item);
	return 0;
}
CItemFactroy& CItemFactroy::Instance()
{
	static CItemFactroy instance;
	return instance;
}