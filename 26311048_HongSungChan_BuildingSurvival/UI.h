#pragma once
#include "glc2d.h"

enum class UIType
{
	Bar,
	Text
};

// Base class for screen-space UI (not affected by the Camera)
class UI
{
protected:
	UIType m_uiType;
	VEC2 m_position = { 0.0f, 0.0f };	// Screen coordinates, top-left
	bool m_isActive = true;

	// Called whenever the position changes, so subclasses can relayout
	virtual void OnLayoutChanged() {};

public:
	UI(const UIType& uiType) : m_uiType(uiType) {}
	virtual ~UI() = default;

	virtual int Update(float deltaTime) { return 0; };
	virtual int Render() = 0;

	UIType GetUIType() const { return m_uiType; };

	VEC2 GetPosition() const { return m_position; };
	void SetPosition(const VEC2& pos) { m_position = pos; OnLayoutChanged(); };

	bool IsActive() const { return m_isActive; };
	void SetActive(const bool isActive) { m_isActive = isActive; };
};
