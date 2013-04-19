#include "StartScene.h"
#include "UIObjectFactory.h"
#include "UIFrame.h"
#include "DrawTextTextScene.h"
#include "ImageTestScene.h"
class AutoRegister
{
public:
	AutoRegister()
	{
		sUIFrame.GetObjFactory()->Register("StartScene",CStartScene::Create);
		sUIFrame.GetObjFactory()->Register("TextScene",CDrawTextTextScene::Create);
		sUIFrame.GetObjFactory()->Register("ImageScene",CImageTestScene::Create);
	}
};
static AutoRegister g;