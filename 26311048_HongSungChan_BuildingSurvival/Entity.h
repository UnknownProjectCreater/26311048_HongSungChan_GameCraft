#pragma once
#include "Camera.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include "glc2d.h"

class Entity : public GameObject
{
private:
	VEC2 m_velocity;
	float m_hp;

protected:
	Animator m_animator;

	virtual int UpdateState(float deltaTime) = 0;

public:
	int Update(float deltaTime) override;
	int Render(const Camera& camera) override;

	VEC2 GetVelocity() const { return m_velocity; };
	void SetVelocity(const VEC2& vel) { m_velocity = vel; };

	float GetHP() const { return m_hp; };
	void SetHP(const float hp) { m_hp = hp; };
};