#pragma once
class CBaseItem;
class CGame;
class CItemFactroy
{
private:
	CItemFactroy(void);
	~CItemFactroy(void);
public:
	static CItemFactroy& Instance();
	CBaseItem* CreateItem(CGame* game);
};

