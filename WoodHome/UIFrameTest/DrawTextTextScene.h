#pragma once
#include "scene.h"
class CDrawTextTextScene :
	public CScene
{
public:
	static CUIObject* Create(){return new CDrawTextTextScene;}
	CDrawTextTextScene(void);
	~CDrawTextTextScene(void);
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual void Load(const slim::XmlNode* node);
	void OnBtnbackClick();
};

