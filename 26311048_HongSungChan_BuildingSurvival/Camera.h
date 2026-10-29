#pragma once
#include "GameObject.h"

class Camera
{
private:
	VEC2 m_position;
	float m_viewWidth;
	float m_viewHeight;

public:
	Camera(float width, float height) :
		m_position(0.0f, 0.0f), m_viewWidth(width), m_viewHeight(height) { }

	VEC2 GetPosition() const { return m_position; };
	void SetPosition(const VEC2& pos) { m_position = pos; };

	void SetViewportSize(float width, float height) {
		m_viewWidth = width;
		m_viewHeight = height;
	}

	VEC2 WorldToScreen(const VEC2& world) const {
		return VEC2{ world.x - m_position.x + m_viewWidth / 2.0f,
					 world.y - m_position.y + m_viewHeight / 2.0f };
	}

	VEC2 ScreenToWorld(const VEC2& screen) const {
		return VEC2{ screen.x + m_position.x - m_viewWidth / 2.0f,
					 screen.y + m_position.y - m_viewHeight / 2.0f };
	}

	void Follow(const VEC2& targetPosition) { m_position = targetPosition; }
};