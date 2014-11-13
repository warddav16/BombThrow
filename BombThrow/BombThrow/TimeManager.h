
#pragma once

#include <Windows.h>

class TimeManager
{
public:
	static TimeManager& Instance()
	{
		static TimeManager instance;
		return instance; //Fancy singleton pattern
	}

	~TimeManager(void);

	float CalculateDelta();


private:
	TimeManager(void);
	TimeManager(TimeManager const&) {}
	void operator=(TimeManager const&) {}

	unsigned long m_currentTime;
};

