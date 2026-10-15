#pragma once
#include "Scene.h"

class GameStartScene : public Scene
{
	int Init() override;
	void Destroy() override;
	int Update() override;
	int Render() override;
};