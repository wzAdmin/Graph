#include "ItemFactroy.h"
#include "Item_2X1.h"

CItemFactroy::CItemFactroy(void)
{
}


CItemFactroy::~CItemFactroy(void)
{
}

CBaseItem* CItemFactroy::CreateItem(CGame* game)
{
	CBaseItem* item = new CItem_2X1(game);
	if(item->Initialize())
		return item;
	else
		delete item;
	return 0;
}
CItemFactroy& CItemFactroy::Instance()
{
	static CItemFactroy instance;
	return instance;
}