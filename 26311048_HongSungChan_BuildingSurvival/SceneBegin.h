#pragma once
#include "Scene.h"

class SceneBegin : public Scene
{
public:
	SceneBegin();
	virtual ~SceneBegin() = default;

	int Init() override;
	void Destroy() override;
	int Render() override;
	int Update() override;
};