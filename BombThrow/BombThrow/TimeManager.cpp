#include "TimeManager.h"


TimeManager::TimeManager(void)
{
	m_currentTime = timeGetTime();
}


TimeManager::~TimeManager(void)
{
}

float TimeManager::CalculateDelta()
{
	unsigned long currTime = timeGetTime();
	float delta = ((float)currTime - m_currentTime) / 1000.0f;
	m_currentTime = currTime;
	return delta;
}