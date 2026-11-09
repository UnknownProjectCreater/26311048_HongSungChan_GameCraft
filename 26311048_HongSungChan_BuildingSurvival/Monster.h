#pragma once
#include <vector>
#include "Entity.h"
#include "FindPath.h"

class Player;

class Monster : public Entity
{
private:
	static constexpr float PATH_INTERVAL = 0.5f;

	// Indices into TileManager::m_tiles. nextTile == nowTile means standing still
	int nowTile = 0;
	int nextTile = 0;

	// m_path[m_pathStep] is the tile being walked to, so each move only goes one tile further
	std::vector<Tile> m_path;
	size_t m_pathStep = 0;
	float m_pathTimer = PATH_INTERVAL;

	const Player* m_target = nullptr;
	FindPath m_findPath;

	void UpdatePath(float deltaTime);
	void UpdateTileMove(float deltaTime);
	VEC2 GetStandPosition(int tile) const;

public:
	int Update(float deltaTime) override;

	void SetStartTile(int tile);
	void SetTarget(const Player* target) { m_target = target; };

	int GetNowTile() const { return nowTile; };
	int GetNextTile() const { return nextTile; };
};
