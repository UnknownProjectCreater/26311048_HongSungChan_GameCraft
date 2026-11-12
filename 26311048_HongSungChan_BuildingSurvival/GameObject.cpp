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

void GameObject::BeginCollisionUpdate()
{
	m_previousColliders = std::move(m_currentColliders);
	m_currentColliders.clear();
}

void GameObject::AddCollider(GameObject* other, CollisionDirection direction)
{
	if (m_currentColliders.find(other) != m_currentColliders.end())
		return;

	CollisionInfo info;

	info.m_other = other;
	info.m_collisionDir = direction;

	m_currentColliders[other] = info;
}

void GameObject::ProcessCollision()
{
	for (const auto& collider : m_currentColliders)
	{
		if (m_previousColliders.find(collider.first) == m_previousColliders.end())
			OnCollisionEnter(collider.second);
		else
			OnCollisionStay(collider.second);
	}

	for (const auto& previousCollider : m_previousColliders)
	{
		if (m_currentColliders.find(previousCollider.first) == m_currentColliders.end())
			OnCollisionExit(previousCollider.second);
	}
}