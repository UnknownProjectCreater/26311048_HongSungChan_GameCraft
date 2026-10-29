#pragma once
#include "Scene.h"

class SceneStart : public Scene
{
public:
	SceneStart();
	virtual ~SceneStart() = default;

	int Init() override;
	void Destroy() override;
	int Render() override;
	int Update() override;
};

