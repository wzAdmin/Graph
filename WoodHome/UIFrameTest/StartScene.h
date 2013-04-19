#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
public:
	static CUIObject* Create(){return new CStartScene;}
	CStartScene(void);
	~CStartScene(void);
private:
	virtual void Load(const slim::XmlNode* node);
	void OnBtn1Click();
	void OnBtn3Click();
};
