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

	m_currentBGM = GetSoundManager()->GetSound("Bgm_Intro");
	g2_SoundPlay(m_currentBGM, true);

	m_font1 = g2_FontCreate("깍두기 도면체", 100);

	return 0;
}

void SceneBegin::Destroy()
{
	g2_SoundStop(m_currentBGM);
}

int SceneBegin::Render(Camera& camera)
{
	VEC2i position{ 10, 10 };
	g2_FontDrawText(m_font1, position, 0xFFFFFFFF, "Press SPACE");

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
