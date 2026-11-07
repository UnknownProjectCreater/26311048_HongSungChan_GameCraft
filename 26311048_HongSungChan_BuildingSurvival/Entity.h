#pragma once
#include "Camera.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "glc2d.h"

enum class EntityDir
{
	FRONT = 0,
	BACK,
	RIGHT,
	LEFT
};

class Entity : public GameObject
{
private:
	VEC2 m_velocity;
	float m_hp;

	EntityDir m_dir = EntityDir::FRONT;

protected:
	Animator m_animator;

	virtual int UpdateState(float deltaTime) = 0;

public:
	int Update(float deltaTime) override;
	int Render(Camera& camera) override;

	VEC2 GetVelocity() const { return m_velocity; };
	void SetVelocity(const VEC2& vel) { m_velocity = vel; };

	float GetHP() const { return m_hp; };
	void SetHP(const float hp) { m_hp = hp; };

	EntityDir GetEntityDir() const { return m_dir; };
	void SetEntityDir(const EntityDir& dir) { m_dir = dir; };
};