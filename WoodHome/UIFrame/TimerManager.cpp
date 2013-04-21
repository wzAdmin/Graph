#include "TimerManager.h"
#include "Trace.h"
#include <Windows.h>

CTimerManager::CTimerManager(void):mCurValiadID(1),mCurTime(0)
{
}


CTimerManager::~CTimerManager(void)
{
}

void CTimerManager::TimerUpdate()
{
	RemoveTimer();
	AddTimer();
	int interval = GetTickCount() - mCurTime;
	mCurTime = GetTickCount();
	DebugTrace("Timermgr interval %d\n",interval);
	TimerIterator it = mTimers.begin();
	for ( ; mTimers.end() != it ; it++)
	{
		it->second.interval_cur += interval;
		int leftTime = it->second.interval_cur - it->second.interval_all;
		if(leftTime >=0 )
		{
			it->second.listener->OnTimer(it->first);
			it->second.interval_cur = 0;
		}
	}
}

void CTimerManager::RemoveTimer( TimerID id )
{
	TimerIterator it = mTimers.find(id);
	if(mTimers.end() != it)
		it->second.toBeremove = true;
	else
	{
		DebugTrace("Timer %d not find\n",id);
	}
}

void CTimerManager::RemoveTimer()
{
	TimerIterator it = mTimers.begin();
	for ( ; mTimers.end() != it ; it++)
	{
		if(it->second.toBeremove)
		{
			mTimers.erase(it);
			it = mTimers.begin();
		}
	}
}

TimerID CTimerManager::CreateTimer( ITimerListener* listener,int interval )
{
	TimerID id = mCurValiadID++;
	Timer timer_new ;
	timer_new.interval_cur = 0;
	timer_new.interval_all = interval;
	timer_new.listener = listener;
	timer_new.toBeremove = false;
	mTimersToAdd.insert(TimerPair(id,timer_new));
	return id;
}

void CTimerManager::OnTimer( TimerID id )
{
	TimerIterator it = mTimers.find(id);
	if(mTimers.end() != it)
		it->second.listener->OnTimer(id);
	else
	{
		DebugTrace("CTimerManager::OnTimer can not find the timer %d \n" ,id);
	}
}

void CTimerManager::AddTimer()
{
	TimerIterator it = mTimersToAdd.begin();
	for ( ; mTimersToAdd.end() != it ; it++)
	{
		mTimers.insert(TimerPair(it->first,it->second));
	}
}
