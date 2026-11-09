#include "TileManager.h"
#include <iostream>

static TileManager* g_tileManager;

TileManager::TileManager()
{
	g_tileManager = this;
}

int TileManager::CreateTiles(Map mapSize, float tileSize, const std::string& key, const VEC2& startPos)
{
	if (0 >= mapSize.x || 0 >= mapSize.y || 0.0f >= tileSize)
		return -1;

	DestroyTiles();

	m_width = mapSize.x;
	m_height = mapSize.y;
	m_tileSize = tileSize;
	m_tiles.reserve(mapSize.x * mapSize.y);

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			auto tile = std::make_unique<Tile>();
			if (0 > tile->Init(key))
			{
				DestroyTiles();
				return -1;
			}

			tile->SetActive(true);
			tile->SetPosition(VEC2(startPos.x + x * tileSize, startPos.y + y * tileSize));
			tile->SetTileType(TileType::None);

			int index = (int)m_tiles.size();
			tile->SetArrayPos(index % mapSize.x, index / mapSize.x);

			FitToCell(tile.get());

			m_tiles.push_back(std::move(tile));
		}
	}

	return 0;
}

void TileManager::DestroyTiles()
{
	for (const auto& tile : m_tiles)
		tile->Destroy();

	m_tiles.clear();
	m_width = 0;
	m_height = 0;
}

int TileManager::Render(Camera& camera)
{
	for (const auto& tile : m_tiles)
		tile->Render(camera);

	return 0;
}

int TileManager::SetTileTexture(int x, int y, const std::string& key)
{
	Tile* tile = GetTile(x, y);
	if (tile == nullptr)
		return -1;

	if (0 > GetTextureManager()->GetTexture(key).m_texture)
		return -1;

	tile->SetTexture(key);
	FitToCell(tile);

	return 0;
}

Tile* TileManager::GetTile(int x, int y) const
{
	int index = GetTileIndex(x, y);
	if (0 > index)
		return nullptr;

	return m_tiles[index].get();
}

Tile* TileManager::GetTile(int index) const
{
	if (index < 0 || index >= m_tiles.size())
		return nullptr;

	return m_tiles[index].get();
}

int TileManager::AsignObjectToTile(VEC2 pos, TileType type)
{
	int index = pos.y * m_width + pos.x;

	if (index < 0 || index >= m_tiles.size())
		return -1;

	m_tiles[index]->SetTileType(type);

	return 0;
}

int TileManager::GetTileIndex(int x, int y) const
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return -1;

	return y * m_width + x;
}

VEC2 TileManager::GetTileCenter(int index) const
{
	if (index < 0 || index >= m_tiles.size())
		return VEC2(0.0f, 0.0f);

	VEC2 position = m_tiles[index]->GetPosition();

	return VEC2(position.x + m_tileSize / 2.0f, position.y + m_tileSize / 2.0f);
}

bool TileManager::IsInLimit(const VEC2& position) const
{
	if (m_tiles.empty())
		return false;

	VEC2 start = m_tiles[0]->GetPosition();

	bool value = position.x <= start.x || position.x >= start.x + m_width * m_tileSize
		|| position.y <= start.y || position.y >= start.y + m_height * m_tileSize;

	std::cout << value;

	return value;
}

void TileManager::FitToCell(Tile* tile) const
{
	int texture = tile->GetTexture();

	tile->SetScaling(VEC2(m_tileSize / g2_TextureWidth(texture), m_tileSize / g2_TextureHeight(texture)));
}

TileManager* GetTileManager()
{
	return g_tileManager;
}