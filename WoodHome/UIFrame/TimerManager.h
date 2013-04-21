#pragma once
#include <map>
#include "UItype.h"
typedef int TimerID;
class UI_API ITimerListener
{
public:
	virtual void OnTimer(TimerID timerid) = 0;
};
typedef struct _Timer
{
	int interval_all;
	int interval_cur;
	ITimerListener* listener;
	bool toBeremove;
}Timer;
class UI_API CTimerManager
{
public:
	CTimerManager(void);
	~CTimerManager(void);
public:
	TimerID CreateTimer(ITimerListener* listener,int  interval);
	void RemoveTimer(TimerID id);
	void OnTimer(TimerID id);
	void TimerUpdate();
private:
	void RemoveTimer();
	void AddTimer();
private:
	typedef std::map<TimerID ,Timer>::iterator TimerIterator;
	typedef std::pair<TimerID ,Timer> TimerPair;
	std::map<TimerID , Timer> mTimers;
	std::map<TimerID , Timer> mTimersToAdd;
	TimerID mCurValiadID;
	int mCurTime;
};

