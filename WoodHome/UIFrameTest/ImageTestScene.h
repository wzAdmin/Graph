#pragma once
#include "scene.h"
class CImageTestScene :
	public CScene
{
public:
	static CUIObject* Create(){return NEW_LEAKCHECK CImageTestScene;}
	CImageTestScene(void);
	~CImageTestScene(void);
private:
	virtual void Draw(CGraphics* pGraphic);
	virtual void Load(const slim::XmlNode* node);
	void OnBtnbackClick();
	void OnBtnScaleXClick();
	void OnBtnScaleYClick();
	void OnBtnRotateClick();
	void OnBtnSkewXClick();
	void OnBtnSkewYClick();
private:
	float mRotate;
	float mScaleX;
	float mScaleY;
	float mSkewX;
	float mSkewY;
};

