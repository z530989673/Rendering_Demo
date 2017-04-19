#ifndef __TIMER__
#define __TIMER__

#include <windows.h>

class Timer {
private:
	static double m_gameStartTime;
	static double m_lastUpdateTime;
	static double m_deltaTime;
	static LARGE_INTEGER m_frequency;
	static LARGE_INTEGER m_counter;

public:
	Timer();
	~Timer();
	static void Start();
	static double GetTime();
	static double GetTimeSinceGameStart();
	static float GetDeltaTime() { return (float)m_deltaTime; }
	static void Update();
};


#endif