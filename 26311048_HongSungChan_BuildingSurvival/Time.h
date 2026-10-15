#pragma once
#include <Windows.h>

struct Time
{
private:
	LARGE_INTEGER periodFrequency	{};
	LARGE_INTEGER lastTime			{};
	LARGE_INTEGER currentTime		{};

	double timeScale;
	long long deltaTime{};		// millisecond
public:
	Time();

	int Init();
	int Update();

	long long GetDeltaTime() const { return deltaTime; };
};