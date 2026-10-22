#include "GameInput.h"

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
	return VEC3i();
}

int GameInput::MouseDelta() const
{
	return 0;
}

int GameInput::GetKeyState(KEYCODE keyCode) const
{
	return 0;
}

GameInput* GetGameInput()
{
	return nullptr;
}
