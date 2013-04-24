#include "EffectFactory.h"
#include "Trace.h"

CEffectFactory::CEffectFactory(void)
{
}

CEffectFactory::~CEffectFactory(void)
{
}

bool CEffectFactory::Register( EffectType effect , CreateFunc func )
{
	CreaterIt it = mCreaterMap.find(effect);
	if(mCreaterMap.end() != it)
	{
		DebugTrace(Trace_Warning,"CEffectFactory::Register fail %d is exsited\n",effect);
		return false;
	}
	else
	{
		mCreaterMap.insert(CreaterPair(effect, func));
		return true;
	}
}

CSceneEffect* CEffectFactory::CreateEffect( EffectType effect , IEffectListner* listner , int interval , int Frames ,CGraphics* pGraphic )
{
	CreaterIt it = mCreaterMap.find(effect);
	if(mCreaterMap.end() != it)
	{
		return (*it->second)(listner,interval,Frames,pGraphic);
	}
	else
	{
		DebugTrace(Trace_Error,"CEffectFactory::CreateEffect fail %d is not exsited\n",effect);
		return NULL;
	}
}
