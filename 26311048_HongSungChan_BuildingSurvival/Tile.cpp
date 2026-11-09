#include "Tile.h"

int Tile::Init(const std::string& key)
{
	SetTag(Tag::Tile);
	SetTileType(TileType::None);

	return GameObject::Init(key);
}

void Tile::SetTileType(TileType type)
{
	tileType = type;

	switch (type)
	{
	case TileType::None:
		cost = 1;
		break;
	case TileType::Obstacle:
		cost = 5;
		break;
	case TileType::Structure:
		cost = 10;
		break;
	}
}

int Tile::Update(float deltaTime)
{
	return 0;
}

int Tile::Render(Camera& camera)
{
	RECT frame{ 0, 0, g2_TextureWidth(m_image.m_texture), g2_TextureHeight(m_image.m_texture) };

	VEC2 screen = camera.WorldToScreen(m_position);

	g2_Draw2D(m_image.m_texture, &frame, &screen, &m_image.m_scaling);

	return 0;
}