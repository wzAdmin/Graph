#include "TimerManager.h"
#include "Trace.h"
#include <Windows.h>

CTimerManager::CTimerManager(void):mbRunning(false),mCurValiadID(1)
{
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mCondMutex,&mutexattr);
	pthread_mutexattr_destroy(&mutexattr);
	pthread_cond_init(&mCond,NULL);
}


CTimerManager::~CTimerManager(void)
{
	if(mbRunning)
	{
		void* re = NULL;
	 	mbRunning = false;
		pthread_join(mThreadId,&re);
	}
 	pthread_cond_destroy(&mCond);
 	pthread_mutex_destroy(&mCondMutex);
}
void CTimerManager::Start()
{
	if(mbRunning)
	{
		DebugTrace("Timermanager is already running\n");
		return;
	}
	mbRunning = true;
	pthread_attr_t attr ;
	pthread_attr_init(&attr);
	pthread_create(&mThreadId,&attr,CTimerManager::TimerThreadFunc,this);
	pthread_attr_destroy(&attr);
}
void* CTimerManager::TimerThreadFunc( void* param )
{
	CTimerManager* pManager = (CTimerManager*)param;
	int a = GetTickCount();
	while (pManager->mbRunning)
	{
		union {
			long long ns100;
			FILETIME ft;
		} now;
		DebugTrace("Timermanager is running %d \n",GetTickCount() -a);
		a = GetTickCount();
		GetSystemTimeAsFileTime (&now.ft);
 		struct timeval tv;
		struct timespec outtime;
		tv.tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
		tv.tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
		outtime.tv_nsec = tv.tv_usec * 1000 + sMinInterval * 1000 * 1000;
		outtime.tv_sec = tv.tv_sec;
		if(outtime.tv_nsec >= 1000000000)
		{
			outtime.tv_sec++;
			outtime.tv_nsec -= 1000000000;
		}
 		pthread_mutex_lock(&pManager->mCondMutex);
		pthread_cond_timedwait(&pManager->mCond,&pManager->mCondMutex,&outtime);
		pthread_mutex_unlock(&pManager->mCondMutex);
	}
	return NULL;
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
