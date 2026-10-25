#include "SceneBegin.h"

SceneBegin::SceneBegin()
{
	m_sceneType = GamePhase::BEGIN;
	m_font1 = g2_FontCreate("깍두기 도면체", 20);
}

int SceneBegin::Init()
{
	return 0;
}

void SceneBegin::Destroy()
{
	
}

int SceneBegin::Render()
{
	g2_FontDrawText(m_font1, { 10, 40 }, 0xFFFFFFFF, "Mouse: %d, %d", g2_GetMouseX(), g2_GetMouseY());

	return 0;
}

int SceneBegin::Update()
{
	const KEYCODE* keys = g2_GetKeyboard();

	if (keys[VK_SPACE] == EINPUT_DOWN)
		g_pApp->ChageScene(GamePhase::START);

	return 0;
}
