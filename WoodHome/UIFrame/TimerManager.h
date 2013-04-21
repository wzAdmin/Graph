#pragma once
#include "pthread.h"
#include <map>
typedef int TimerID;
class ITimerListener
{
public:
	virtual void OnTimer(TimerID timerid) = 0;
};
typedef struct _Timer
{
	int interval_all;
	int interval_cur;
	ITimerListener* listener;
}Timer;
class CTimerManager
{
public:
	CTimerManager(void);
	~CTimerManager(void);
public:
	void Start();
	TimerID CreateTimer(ITimerListener* listener,int  interval);
	void RemoveTimer(TimerID id);
	void OnTimer(TimerID id);
private:
	static void* TimerThreadFunc(void* param);
private:
	typedef std::map<TimerID ,Timer>::iterator TimerIterator;
	typedef std::pair<TimerID ,Timer> TimerPair;
	std::map<TimerID , Timer> mTimers;
	TimerID mCurValiadID;
	bool mbRunning;

	pthread_t mThreadId;
	pthread_mutex_t mCondMutex;
	pthread_cond_t  mCond;
	//the min interval is 10ms
	static const int sMinInterval = 10;
};

