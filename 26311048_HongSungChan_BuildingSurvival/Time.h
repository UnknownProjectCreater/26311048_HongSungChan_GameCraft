#pragma once

struct Time
{
private:
	long long periodFrequency	{};
	long long lastTime			{};
	long long currentTime		{};

	double timeScale;

public:
	int Init();
	int Update();

	long long beginTime		{};
	long long eplapsedTime	{};
	long long deltaTime		{};		// millisecond
};