#include "StartScene.h"
#include "UIObjectFactory.h"
#include "UIFrame.h"
#include "DrawTextTextScene.h"
#include "ImageTestScene.h"
#include "EffectTest.h"
#include "ListScene.h"
class AutoRegister
{
public:
	AutoRegister()
	{
		sUIFrame.GetObjFactory()->Register("StartScene",CStartScene::Create);
		sUIFrame.GetObjFactory()->Register("TextScene",CDrawTextTextScene::Create);
		sUIFrame.GetObjFactory()->Register("ImageScene",CImageTestScene::Create);
		sUIFrame.GetObjFactory()->Register("EffectScene",CEffectTest::Create);
		sUIFrame.GetObjFactory()->Register("ListScene",CListScene::Create);
	}
};
static AutoRegister g;