#pragma once
#include "Scene.h"

class SceneBegin : public Scene
{
public:
	SceneBegin();

	int Init() override;
	void Destroy() override;
	int Render() override;
	int Update() override;
};