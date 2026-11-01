#include "ScenePlay.h"
#include "GameInput.h"
#include "Player.h"
#include "App.h"

extern App* g_pApp;

ScenePlay::ScenePlay()
{

}

int ScenePlay::Init()
{
	m_sceneType = GamePhase::PLAY;

	m_player = g_pApp->GetGameManager()->CreateSceneObject<Player>();
	if (0 > m_player->Init("Player_Idle"))
		return -1;

	m_player->SetScaling(VEC2(2.0f, 2.0f));
	m_player->SetPosition(VEC2(0.0f, 0.0f));

	return 0;
}

void ScenePlay::Destroy()
{
	m_player = nullptr;
}

int ScenePlay::Render(const Camera& camera)
{
	g_pApp->GetGameManager()->Render(camera);

	return 0;
}

int ScenePlay::Update(float deltaTime)
{
	g_pApp->GetGameManager()->Update(g_pApp->GetDeltaTime());

	return 0;
}
