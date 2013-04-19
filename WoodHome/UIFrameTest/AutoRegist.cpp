#include "StartScene.h"
#include "UIObjectFactory.h"
#include "UIFrame.h"
class AutoRegister
{
public:
	AutoRegister()
	{
		sUIFrame.GetObjFactory()->Register("StartScene",CStartScene::Create);
	}
};
static AutoRegister g;