#include "Tile.h"

int Tile::Init(const std::string& key)
{
	SetTag(Tag::Tile);

	return GameObject::Init(key);
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