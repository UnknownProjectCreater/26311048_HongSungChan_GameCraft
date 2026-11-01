#include "App.h"
#include "GameInput.h"
#include "TextureManager.h"
#include "SceneBegin.h"
#include "ScenePlay.h"

App* g_pApp;

void App::ChageScene(GamePhase nextScene)
{
	m_sceneChanged = true;
	m_sceneNext = nextScene;
}

App::App()
{
	g_pApp = this;
	m_pGameInput = new GameInput;
	m_pGameManager = new GameManager;
	m_textureManager = new TextureManager;
	m_pCamera = new Camera((float)m_gameWindow.m_screenWidth, (float)m_gameWindow.m_screenHeight);

	m_scenes[GamePhase::BEGIN] = new SceneBegin;
	m_scenes[GamePhase::PLAY] = new ScenePlay;
	//m_scenes[GamePhase::RESULT] = new 

	m_pCurrentScene = m_scenes[GamePhase::BEGIN];
}

App::~App()
{
	Destroy();
}

int App::Init()
{
	if (0 > m_gameGraphicEngine.Init(&m_gameWindow))
		return -1;

	m_gameGraphicEngine.SetColor(0xFF006699);

	g2_FontRegisterFile("Resource/Font/KkakdugiDrafting-Regular.ttf");

	m_gameTime.Init();

	// Init Object
	// Init Rendering

	if (0 > m_pGameInput->Init())
	{
		Destroy();
		return -2;
	}

	if (0 > m_textureManager->Init())
	{
		Destroy();
		return -4;
	}

	if (0 > m_pCurrentScene->Init())
	{
		Destroy();
		return -3;
	}

	return 0;
}

void App::Destroy()
{
	if (m_pGameInput)
	{
		delete m_pGameInput;
		m_pGameInput = nullptr;
	}

	if (m_pGameManager)
	{
		delete m_pGameManager;
		m_pGameManager = nullptr;
	}

	if (m_textureManager)
	{
		delete m_textureManager;
		m_textureManager = nullptr;
	}

	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	for (const auto& [id, scene] : m_scenes)
	{
		delete scene;
	}
	m_scenes.clear();
}

int App::Update(float deltaTime)
{
	if (m_sceneChanged)
	{
		m_pCurrentScene->Destroy();
		m_pGameManager->DestroySceneObjects();

		m_sceneChanged = false;
		m_sceneCurrent = m_sceneNext;
		m_pCurrentScene = m_scenes[m_sceneCurrent];

		m_pCurrentScene->Init();
	}

	if (0 > m_pGameInput->Update())
		return -1;

	if (0 > m_pCurrentScene->Update(deltaTime))
		return -1;

	// Game UI Update
	// GameObject Update

	return 0;
}

int App::Render(const Camera& camera)
{
	// About Scene
	// GameObject Render
	// Game UI Render
	if (0 > m_pCurrentScene->Render(camera))
	{
		return -1;
	}

	return 0;
}

int App::Run()
{
	m_gameGraphicEngine.Run();

	this->Destroy();
	return 0;
}