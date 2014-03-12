#include "pch.h"
#include "Timer.h"


#include "Timer.h"


Timer::Timer(void)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&zeroTime);
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	previousTime=zeroTime;
	pausedTime=0;
	delta=0;
}


Timer::~Timer(void)
{
}

void Timer::Tick()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&totalTime);
	delta=totalTime-previousTime;
	previousTime=totalTime;
	if(pause==true) 
	{
		pausedTime+=delta;
		delta=0;
	}
}

void Timer::Pause()
{
	pause=true;
}

void Timer::Start()
{
	pause=false;
}

float Timer::GetDelta()
{
	return (float)delta/countsPerSec;
}

__int64 Timer::GetTotal()
{
	 return (totalTime-zeroTime)/countsPerSec;
}

float Timer::GetTotalFloat()
{
	 return (totalTime-zeroTime)/(float)countsPerSec;
}

float Timer::GetDynamicDelta()
{
	long long now;
	QueryPerformanceCounter((LARGE_INTEGER*)&now);
	return ((long long)now - totalTime )/ (float)countsPerSec;
}