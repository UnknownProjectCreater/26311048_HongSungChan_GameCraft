#include "ScenePlay.h"
#include "GameInput.h"
#include "Player.h"
#include "Zombie.h"
#include "App.h"

extern App* g_pApp;

static const float PLAYER_SPEED = 200.0f;

bool IsKeyHeld(KEYCODE keyCode)
{
	auto keyEvent = GetGameInput()->GetKeyState(keyCode);
	return keyEvent == EINPUT_DOWN || keyEvent == EINPUT_PRESS;
}

ScenePlay::ScenePlay()
{

}

int ScenePlay::Init()
{
	m_sceneType = GamePhase::PLAY;

	m_player = g_pApp->GetGameManager()->CreateSceneObject<Player>();
	if (0 > m_player->Init("Player_Idle"))
		return -1;

	m_player->SetScaling(VEC2(5.0f, 5.0f));
	m_player->SetPosition(VEC2(0.0f, 0.0f));

	m_zombie = g_pApp->GetGameManager()->CreateSceneObject<Zombie>();
	if (0 > m_zombie->Init("Zombie_Idle"))
		return -1;

	m_zombie->SetScaling(VEC2(5.0f, 5.0f));
	m_zombie->SetPosition(VEC2(100.0f, 0.0f));

	return 0;
}

void ScenePlay::Destroy()
{
	m_player = nullptr;
	m_zombie = nullptr;
}

int ScenePlay::Render(const Camera& camera)
{
	g_pApp->GetGameManager()->Render(camera);

	return 0;
}

int ScenePlay::Update(float deltaTime)
{
	UpdatePlayerInput();

	g_pApp->GetGameManager()->Update(g_pApp->GetDeltaTime());

	return 0;
}

void ScenePlay::UpdatePlayerInput()
{
	VEC2 velocity(0.0f, 0.0f);

	if (IsKeyHeld('W'))
		velocity.y -= PLAYER_SPEED;
	else if (IsKeyHeld('S'))
		velocity.y += PLAYER_SPEED;
	else if (IsKeyHeld('A'))
		velocity.x -= PLAYER_SPEED;
	else if (IsKeyHeld('D'))
		velocity.x += PLAYER_SPEED;

	if (velocity.x > 0.0f)
		m_player->SetEntityDir(EntityDir::RIGHT);
	else if (velocity.x < 0.0f)
		m_player->SetEntityDir(EntityDir::LEFT);
	else if (velocity.y < 0.0f)
		m_player->SetEntityDir(EntityDir::BACK);
	else if (velocity.y > 0.0f)
		m_player->SetEntityDir(EntityDir::FRONT);

	m_player->SetVelocity(velocity);
}
