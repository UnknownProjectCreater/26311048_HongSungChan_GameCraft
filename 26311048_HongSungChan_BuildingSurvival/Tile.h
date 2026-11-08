#pragma once
#include "Camera.h"
#include "GameObject.h"

class Tile : public GameObject
{
private:
	int cost;

public:
	int Init(const std::string& key) override;
	int Update(float deltaTime) override;
	int Render(Camera& camera) override;

	int GetCost() const { return cost; };
};