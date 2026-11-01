#pragma once
#include "glc2d.h"

class GameInput
{
public:
	int Init();
	int Update();

public:
	GameInput();

	VEC3i MousePosition() const;
	int MouseDelta() const;
	int GetKeyState(KEYCODE keycode) const;
	int GetMouseEvent(int nMouse) const;
};

extern GameInput* GetGameInput();