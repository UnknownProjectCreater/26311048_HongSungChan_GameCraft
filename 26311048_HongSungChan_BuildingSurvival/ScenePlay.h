#pragma once
#include "Scene.h"
#include "Entity.h"

class ScenePlay : public Scene
{
private:
	Entity* m_player;
	Entity* m_zombie;

	void UpdatePlayerInput();

public:
	ScenePlay();
	virtual ~ScenePlay() = default;

	int Init() override;
	void Destroy() override;
	int Render(const Camera& camera) override;
	int Update(float deltaTime) override;
};