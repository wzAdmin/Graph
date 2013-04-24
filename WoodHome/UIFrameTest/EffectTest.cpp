#include "EffectTest.h"
#include "EffectType.h"
#include "UIButton.h"

CEffectTest::CEffectTest(void)
{
}

CEffectTest::~CEffectTest(void)
{
}

void CEffectTest::OnLoad()
{
	CUIButton* btn = (CUIButton*)get("back");
	btn->AddClickListen(this,(OnBtnClick)&CEffectTest::OnBtnbackClick);

	btn = (CUIButton*)get("fadeto");
	btn->AddClickListen(this,(OnBtnClick)&CEffectTest::OnBtnfadetoClick);
}

void CEffectTest::OnBtnbackClick()
{
	Back();
}

void CEffectTest::OnBtnfadetoClick()
{
	Goto(SCENE_DrawText,NULL,Effect_FadeTo);
}
