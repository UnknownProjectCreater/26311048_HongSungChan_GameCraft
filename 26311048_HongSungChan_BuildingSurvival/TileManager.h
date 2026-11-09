#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Tile.h"

class TileManager
{
private:
	std::vector<std::unique_ptr<Tile>> m_tiles;
	int m_width = 0;
	int m_height = 0;
	float m_tileSize = 0.0f;

	void FitToCell(Tile* tile) const;

public:
	TileManager();

	int CreateTiles(Map mapSize, float tileSize, const std::string& key, const VEC2& startPos);
	void DestroyTiles();

	int Render(Camera& camera);

	int SetTileTexture(int x, int y, const std::string& key);
	Tile* GetTile(int x, int y) const;
	Tile* GetTile(int index) const;

	int AsignObjectToTile(VEC2 pos, TileType type);
	int GetTileIndex(int x, int y) const;
	VEC2 GetTileCenter(int index) const;
	bool IsInLimit(const VEC2& position) const;

	int GetWidth() const { return m_width; };
	int GetHeight() const { return m_height; };
};

extern TileManager* GetTileManager();