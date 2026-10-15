#include <Windows.h>
#include "Time.h"

using namespace std;

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

	timeScale = 1.0 / (long long)periodFrequency.QuadPart;
}

int Time::Init()
{
	beginTime		= {};
	eplapsedTime	= {};
	deltaTime		= {};

	return 0;
}

int Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	deltaTime = (long long)(currentTime.QuadPart - lastTime.QuadPart) * timeScale;

	lastTime = currentTime;

	return 0;
}