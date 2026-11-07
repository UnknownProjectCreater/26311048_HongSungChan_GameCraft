#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Scene.h"
#include "Time.h"
#include "GraphicEngine.h"
#include "GameManager.h"
#include "AnimationManager.h"

class TextureManager;
class SoundManager;
class TileManager;
class GameInput;
class GameManager;
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
		false,
		1.0f
	};

	GraphicEngine m_gameGraphicEngine;
	Time m_gameTime;
	GameManager* m_pGameManager;
	GameInput* m_pGameInput;
	Scene* m_pCurrentScene;
	TextureManager* m_textureManager;
	SoundManager* m_soundManager;
	TileManager* m_tileManager;
	Camera* m_pCamera;

	std::unordered_map<GamePhase, Scene*> m_scenes;

public:
	void ChageScene(GamePhase nextScene);
	bool m_sceneChanged = false;
	GamePhase m_sceneCurrent;
	GamePhase m_sceneNext;

public:
	App();
	virtual ~App();

	virtual int Init();
	virtual void Destroy();
	virtual int Render(Camera& camera);
	virtual int Update(float deltaTime);

	int Run();

	GraphicEngine::GameWindow GetGameWindow() const { return m_gameWindow; };
	GameManager* GetGameManager() const { return m_pGameManager; };
	Camera& GetCamera() const { return *m_pCamera; };

	void UpdateTime() { m_gameTime.Update(); };
	float GetDeltaTime() const { return (float)m_gameTime.GetDeltaTime(); };
};

extern App* g_pApp;