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

	int CreateTiles(int width, int height, float tileSize, const std::string& key, const VEC2& origin = VEC2(0.0f, 0.0f));
	void DestroyTiles();

	int Render(Camera& camera);

	int SetTileTexture(int x, int y, const std::string& key);
	Tile* GetTile(int x, int y) const;

	int GetWidth() const { return m_width; };
	int GetHeight() const { return m_height; };
};

extern TileManager* GetTileManager();