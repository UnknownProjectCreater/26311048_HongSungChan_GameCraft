#pragma once
#include "GameObject.h"
#include "glc2d.h"

class Entity : public GameObject
{
private:
	VEC2 m_velocity;
	float m_hp;

public:
	VEC2 GetVelocity() const { return m_velocity; };
	void SetVelocity(const VEC2& vel) { m_velocity = vel; };

	float GetHP() const { return m_hp; };
	void SetHP(const float )
};