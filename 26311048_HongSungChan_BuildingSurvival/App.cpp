#include "App.h"
#include "GameInput.h"
#include "SceneBegin.h"
#include "SceneStart.h"

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

	m_scenes[GamePhase::BEGIN] = new SceneBegin;
	m_scenes[GamePhase::START] = new SceneStart;
	//m_scenes[GamePhase::PLAY] = new 
	//m_scenes[GamePhase::RESULT] = new 

	m_pCurrentScene = m_scenes[GamePhase::BEGIN];
}

App::~App()
{
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
		return -1;
	}

	m_pCurrentScene = new Scene;
	if (0 > m_pCurrentScene->Init())
	{
		Destroy();
		return -1;
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

	if (m_pCurrentScene)
	{
		delete m_pCurrentScene;
		m_pCurrentScene = nullptr;
	}

	for (const auto& [id, scene] : m_scenes)
	{
		delete scene;
	}
	m_scenes.clear();
}

int App::Update()
{
	if (m_sceneChanged)
	{
		m_pCurrentScene->Destroy();

		m_sceneChanged = false;
		m_sceneCurrent = m_sceneNext;
		m_pCurrentScene = m_scenes[m_sceneCurrent];

		m_pCurrentScene->Init();
	}

	m_gameTime.Update();

	if (0 > m_pGameInput->Update())
		return -1;

	if (0 > m_pCurrentScene->Update())
		return -1;
	
	// Game UI Update
	// GameObject Update

	return 0;
}

int App::Render()
{
	// About Scene
	// GameObject Render
	// Game UI Render
	if (0 > m_pCurrentScene->Render())
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