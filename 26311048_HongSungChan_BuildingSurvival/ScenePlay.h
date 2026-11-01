#pragma once
#include "Scene.h"
#include "Entity.h"

class ScenePlay : public Scene
{
private:
	Entity* m_player;

public:
	ScenePlay();
	virtual ~ScenePlay() = default;

	int Init() override;
	void Destroy() override;
	int Render(const Camera& camera) override;
	int Update(float deltaTime) override;
};