#include "TimerManager.h"
#include "Trace.h"

CTimerManager::CTimerManager(void):mbRunning(false),mCurValiadID(1)
{
}


CTimerManager::~CTimerManager(void)
{
}
void CTimerManager::Start()
{
	if(mbRunning)
	{
		DebugTrace("Timermanager is already running\n");
		return;
	}
	mbRunning = true;
}
int CTimerManager::TimerThreadFunc( void* param )
{
	CTimerManager* pManager = (CTimerManager*)param;
	while (pManager->mbRunning)
	{

	}
	return 0;
}

void CTimerManager::RemoveTimer( TimerID id )
{
	TimerIterator it = mTimers.find(id);
	if(mTimers.end() != it)
		mTimers.erase(id);
	else
	{
		DebugTrace("Timer %d not find\n",id);
	}
}

TimerID CTimerManager::CreateTimer( ITimerListener* listener,int interval )
{
	TimerID id = mCurValiadID++;
	Timer timer_new ;
	timer_new.interval_cur = 0;
	timer_new.interval_all = interval;
	timer_new.listener = listener;
	mTimers.insert(TimerPair(id,timer_new));
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
