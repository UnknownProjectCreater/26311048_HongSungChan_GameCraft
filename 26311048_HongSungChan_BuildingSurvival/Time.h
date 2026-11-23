#pragma once
#include <Windows.h>

struct Time
{
private:
	LARGE_INTEGER periodFrequency	{};
	LARGE_INTEGER lastTime				{};
	LARGE_INTEGER currentTime		{};

	double m_timeScale;
	double m_deltaTime{};
public:
	Time();

	int Init();
	int Update();

	double GetDeltaTime() const { return deltaTime; };
};