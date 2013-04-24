#pragma once
#include "EffectType.h"
#include <map>

class IEffectListner;
class CGraphics;
class CSceneEffect;
typedef CSceneEffect* (*CreateFunc)(IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic);
class CEffectFactory
{
public:
	CEffectFactory(void);
	~CEffectFactory(void);
public:
	CSceneEffect* CreateEffect(EffectType effect , IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic);
	bool Register(EffectType effect , CreateFunc func);
private:
	typedef std::map<EffectType , CreateFunc>::iterator CreaterIt;
	typedef std::pair<EffectType , CreateFunc> CreaterPair;
	std::map<EffectType,CreateFunc> mCreaterMap;
};
