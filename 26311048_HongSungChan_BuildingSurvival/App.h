#pragma once
#include <string>
#include "Time.h"
#include "GraphicEngine.h"

class GameInput;
class Scene;

class App
{
protected:
	GraphicEngine::GameWindow m_gameWindow
	{
		100,
		100,
		1920,
		1080,
		"Hallo Welt",
		true,
		1.0f
	};

	GraphicEngine m_gameGraphicEngine	{};
	GameInput* m_pGameInput				{};
	Scene* m_pCurrentScene				{};
	Time m_gameTime						{};
public:
	App();
	virtual ~App();

	int Init();
	void Destroy();
	int Render();
	int Update();

	int Run();
};

extern App* g_pApp;