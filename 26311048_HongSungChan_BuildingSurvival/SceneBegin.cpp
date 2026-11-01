#include "SceneBegin.h"
#include "GameInput.h"
#include "App.h"

extern App* g_pApp;

SceneBegin::SceneBegin()
{

}

int SceneBegin::Init()
{
	m_sceneType = GamePhase::BEGIN;

	return 0;
}

void SceneBegin::Destroy()
{
	
}

int SceneBegin::Render(const Camera& camera)
{
	return 0;
}

int SceneBegin::Update(float deltaTime)
{
	auto keyEvent = GetGameInput()->GetKeyState(VK_SPACE);
	if (keyEvent == EINPUT_DOWN)
	{
		g_pApp->ChageScene(GamePhase::PLAY);
	}

	return 0;
}
