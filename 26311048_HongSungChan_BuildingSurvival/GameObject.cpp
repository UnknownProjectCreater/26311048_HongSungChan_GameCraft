#include "GameObject.h"

int GameObject::Init(const std::string& key)
{
	SetTexture(key);
	if (0 > m_image.m_texture)
		return -1;

	return 0;
}

int GameObject::Destroy()
{
	return 0;
}

void GameObject::SetTexture(const std::string& key)
{
	m_image = GetTextureManager()->GetTexture(key);
}

void GameObject::SetColliderSize(bool useCustomSize, VEC2 size)
{
	if (useCustomSize)
	{
		float width = g2_TextureWidth(m_image.m_texture);
		float height = g2_TextureHeight(m_image.m_texture);
		m_collider = { width, height };

		return;
	}

	m_collider = size;
}