#pragma once
#include <string>
#include "UI.h"
#include "TextureManager.h"

// Horizontal bar that fills from left to right.
// Only change fillAmount (0.0 ~ 1.0); the Fill Area's scale and position
// are recalculated from the Background size automatically.
class Bar : public UI
{
private:
	Texture m_fillAreaImage;
	Texture m_backGroundImage;

	float m_fillAmount = 1.0f;

	// Inset of the Fill Area inside the Background, in screen pixels
	VEC2 m_padding = { 0.0f, 0.0f };

	// Values calculated in UpdateFillArea()
	VEC2 m_fillAreaPosition = { 0.0f, 0.0f };
	VEC2 m_fillAreaScaling = { 0.0f, 0.0f };

	void UpdateFillArea();

protected:
	void OnLayoutChanged() override { UpdateFillArea(); };

public:
	Bar() : UI(UIType::Bar) {}

	int Render() override;

	void SetFillAreaTexture(const std::string& key);
	int GetFillAreaTexture() const { return m_fillAreaImage.m_texture; };

	void SetbackGroundTexture(const std::string& key);
	int GetbackGroundTexture() const { return m_backGroundImage.m_texture; };

	float GetFillAmount() const { return m_fillAmount; };
	void SetFillAmount(float fillAmount);

	// Resize the bar in screen pixels (adjusts the Background scaling)
	void SetSize(const VEC2& size);
	VEC2 GetSize() const;

	VEC2 GetPadding() const { return m_padding; };
	void SetPadding(const VEC2& padding) { m_padding = padding; UpdateFillArea(); };
};
