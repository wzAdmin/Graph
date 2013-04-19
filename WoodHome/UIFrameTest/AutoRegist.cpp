#include "StartScene.h"
#include "UIObjectFactory.h"
#include "UIFrame.h"
#include "DrawTextTextScene.h"
class AutoRegister
{
public:
	AutoRegister()
	{
		sUIFrame.GetObjFactory()->Register("StartScene",CStartScene::Create);
		sUIFrame.GetObjFactory()->Register("TextScene",CDrawTextTextScene::Create);
	}
};
static AutoRegister g;