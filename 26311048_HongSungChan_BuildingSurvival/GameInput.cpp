#include "GameInput.h"

static GameInput* g_input;

GameInput::GameInput()
{
	g_input = this;
}

int GameInput::Init()
{
	return 0;
}

int GameInput::Update()
{
	return 0;
}

VEC3i GameInput::MousePosition() const
{
	return g2_GetMouse();
}

int GameInput::MouseDelta() const
{
	auto r = g2_GetMouse().z;
	return r;
}

int GameInput::GetKeyState(KEYCODE keyCode) const
{
	auto keys = g2_GetKeyboard();
	return keys[keyCode];
}

int GameInput::GetMouseEvent(int nMouse) const
{
	return g2_GetMouseEvent(nMouse);
}

GameInput* GetGameInput()
{
	return g_input;
}
