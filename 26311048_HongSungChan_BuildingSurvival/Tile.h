#pragma once
#include "Camera.h"
#include "GameObject.h"

struct Map
{
	int x;
	int y;
};

enum class TileType
{
	None,
	Obstacle
};

class Tile : public GameObject
{
public:
	// Position inside TileManager::m_tiles, not a world position
	struct arrayPos
	{
		int x;
		int y;
	};

private:
	int cost;
	TileType tileType;
	arrayPos m_arrayPos = { 0, 0 };

public:
	int Init(const std::string& key) override;
	int Update(float deltaTime) override;
	int Render(Camera& camera) override;

	int GetCost() const { return cost; };

	TileType GetTileType() const { return tileType; };
	void SetTileType(TileType type);

	bool IsWalkable() const { return tileType != TileType::Obstacle; };

	arrayPos GetArrayPos() const { return m_arrayPos; };
	void SetArrayPos(int x, int y) { m_arrayPos = { x, y }; };
};