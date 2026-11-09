#pragma once
#include "Scene.h"
#include "Entity.h"

class Player;
class Zombie;

class ScenePlay : public Scene
{
private:
	Player* m_player;
	Zombie* m_zombie;

	void UpdatePlayerInput();

public:
	ScenePlay();
	virtual ~ScenePlay() = default;

	int Init() override;
	void Destroy() override;
	int Render(Camera& camera) override;
	int Update(float deltaTime) override;
};