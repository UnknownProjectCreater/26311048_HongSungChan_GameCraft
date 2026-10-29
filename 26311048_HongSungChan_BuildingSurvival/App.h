#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Scene.h"
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

	std::unordered_map<GamePhase, Scene*> m_scenes;

public:
	void ChageScene(GamePhase nextScene);
	bool m_sceneChanged;
	GamePhase m_sceneCurrent	{};
	GamePhase m_sceneNext		{};

public:
	App();
	virtual ~App();

	virtual int Init();
	virtual void Destroy();
	virtual int Render();
	virtual int Update();

	int Run();

	GraphicEngine::GameWindow GetGameWindow() const { return m_gameWindow; };
};

extern App* g_pApp;