#include "App.h"
#include "GameInput.h"
#include "Scene.h"

App::App()
{

}

App::~App()
{
}

int App::Init()
{
	if (0 > m_gameGraphicEngine.Init())
		return -1;

	//m_gameGraphicEngine.SetColor();

	m_gameTime.Init();

	// Init Object
	// Init Rendering
	
	m_pGameInput = new GameInput;
	if (0 > m_pGameInput->Init())
	{
		delete m_pGameInput;
		return -1;
	}

	m_pCurrentScene = new Scene;
	if (0 > m_pCurrentScene->Init())
	{
		delete m_pCurrentScene;
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
}

int App::Update()
{
	// Time Update
	
	m_gameTime.Update();

	if (0 > m_pGameInput->Update())
		return -1;

	if (0 > m_pCurrentScene->Update())
		return -1;
	
	// About Scene
	// Game UI Update
	// GameObject Update

	return 0;
}

int App::Render()
{
	// About Scene
	// GameObject Render
	// Game UI Render

	return 0;
}

int App::Run()
{
	int hr = 0;

	while (true)
	{
		if (0 > this->Update())
		{
			hr = -1;
			break;
		}

		if (0 > this->Render())
		{
			hr = -2;
			break;
		}
	}

	this->Destroy();
	return 0;
}