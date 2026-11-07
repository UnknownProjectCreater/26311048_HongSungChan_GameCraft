#pragma once
#include "Camera.h"
#include "GameObject.h"

class Tile : public GameObject
{
public:
	int Init(const std::string& key) override;
	int Update(float deltaTime) override;
	int Render(Camera& camera) override;
};