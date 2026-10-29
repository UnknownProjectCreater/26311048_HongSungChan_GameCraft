#pragma once
#include <string>
#include <unordered_map>
#include "glc2d.h"
#include "TextureManager.h"

enum class CollisionDirection
{
	Left,
	Right,
	Top,
	Bottom
};

enum class Tag
{
	None,
	Player,
	Enemy,
	Ground,
	Obstacle
};

struct Texture
{
	VEC2 m_scaling;
	int m_texture;
};

struct CollisionInfo
{
	GameObject* m_other = nullptr;
	CollisionDirection m_collisionDir;
};

struct Collider
{
	int m_width;
	int m_height;
};

class GameObject
{
protected:
	VEC2 m_position;
	Collider m_collider;

	Tag m_tag;
	bool m_isActive;
	bool m_isTrigger;

public:
	std::unordered_map<GameObject*, CollisionInfo> m_colliders;
	std::unordered_map<GameObject*, CollisionInfo> m_previousColliders;

	std::string m_name;
	Texture m_image;

	virtual int Init(TextureType textureId);
	virtual int Update(float deltaTime) = 0;
	virtual int Render() = 0;
	virtual int Destroy();

	virtual void OnCollisionEnter(const CollisionInfo& info) = 0;
	virtual void OnCollisionStay(const CollisionInfo& info) = 0;
	virtual void OnCollisionExit(const CollisionInfo& info) = 0;

	void SetColliderSize();

	void BeginCollisionUpdate();
	void AddCollider(GameObject* other, CollisionDirection direction);
	void ProcessCollision();

	bool IsColliding() const { return !m_colliders.empty(); };

	float GetLeft() const { return m_position.x; };
	float GetRight() const { return m_position.x + m_collider.m_width; };
	float GetTop() const { return m_position.y; };
	float GetBottom() const { return m_position.y + m_collider.m_height; };

	VEC2 GetPosition() const { return m_position; };
	void SetPosition(const VEC2& pos) { m_position = pos; };

	Collider GetCollider() const { return m_collider; };
	void SetCollider(const Collider& col) { m_collider = col; };

	bool IsTrigger() const { return m_isTrigger;; };
	void SetTrigger(const bool& isTrigger) { m_isTrigger = isTrigger; };

	Tag GetTag() const { return m_tag;; };
	void SetTag(const Tag& tag) { m_tag = tag; };

	bool IsActive() const { return m_isActive; };
	void SetActive(const bool isActive) { m_isActive = isActive; };

	int GetTexture() const { return m_image.m_texture; };
	void SetTexture(const TextureType textureId);

	VEC2 GetScaling() const { return m_image.m_scaling; };
	void SetScaling(const VEC2& scale) { m_image.m_scaling = scale; };
};