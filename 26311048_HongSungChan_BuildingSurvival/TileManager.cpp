#include "TileManager.h"

static TileManager* g_tileManager;

TileManager::TileManager()
{
	g_tileManager = this;
}

int TileManager::CreateTiles(int width, int height, float tileSize, const std::string& key, const VEC2& startPos)
{
	if (0 >= width || 0 >= height || 0.0f >= tileSize)
		return -1;

	DestroyTiles();

	m_width = width;
	m_height = height;
	m_tileSize = tileSize;
	m_tiles.reserve(width * height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			auto tile = std::make_unique<Tile>();
			if (0 > tile->Init(key))
			{
				DestroyTiles();
				return -1;
			}

			tile->SetActive(true);
			tile->SetPosition(VEC2(startPos.x + x * tileSize, startPos.y + y * tileSize));
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
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return nullptr;

	return m_tiles[y * m_width + x].get();
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