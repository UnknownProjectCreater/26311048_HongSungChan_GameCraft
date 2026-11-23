#include <algorithm>
#include "Bar.h"

void Bar::SetFillAreaTexture(const std::string& key)
{
	m_fillAreaImage = GetTextureManager()->GetTexture(key);
	UpdateFillArea();
}

void Bar::SetbackGroundTexture(const std::string& key)
{
	m_backGroundImage = GetTextureManager()->GetTexture(key);
	UpdateFillArea();
}

void Bar::SetFillAmount(float fillAmount)
{
	m_fillAmount = std::clamp(fillAmount, 0.0f, 1.0f);
	UpdateFillArea();
}

void Bar::SetSize(const VEC2& size)
{
	if (0 > m_backGroundImage.m_texture)
		return;

	const float texWidth = static_cast<float>(g2_TextureWidth(m_backGroundImage.m_texture));
	const float texHeight = static_cast<float>(g2_TextureHeight(m_backGroundImage.m_texture));
	if (texWidth <= 0.0f || texHeight <= 0.0f)
		return;

	m_backGroundImage.m_scaling = VEC2(size.x / texWidth, size.y / texHeight);
	UpdateFillArea();
}

VEC2 Bar::GetSize() const
{
	if (0 > m_backGroundImage.m_texture)
		return VEC2(0.0f, 0.0f);

	return VEC2(g2_TextureWidth(m_backGroundImage.m_texture) * m_backGroundImage.m_scaling.x,
				g2_TextureHeight(m_backGroundImage.m_texture) * m_backGroundImage.m_scaling.y);
}

void Bar::UpdateFillArea()
{
	if (0 > m_fillAreaImage.m_texture || 0 > m_backGroundImage.m_texture)
		return;

	const float fillTexWidth = static_cast<float>(g2_TextureWidth(m_fillAreaImage.m_texture));
	const float fillTexHeight = static_cast<float>(g2_TextureHeight(m_fillAreaImage.m_texture));
	if (fillTexWidth <= 0.0f || fillTexHeight <= 0.0f)
		return;

	// Area inside the Background that a full (1.0) Fill Area covers
	const VEC2 backGroundSize = GetSize();
	const float innerWidth = (std::max)(0.0f, backGroundSize.x - m_padding.x * 2.0f);
	const float innerHeight = (std::max)(0.0f, backGroundSize.y - m_padding.y * 2.0f);

	// Scale: width proportional to fillAmount, height always fits the inner area
	m_fillAreaScaling.x = (innerWidth * m_fillAmount) / fillTexWidth;
	m_fillAreaScaling.y = innerHeight / fillTexHeight;

	// Position: keep the left edge pinned to the Background's inner left edge,
	// so the bar shrinks toward the left and grows to the right
	m_fillAreaPosition = VEC2(m_position.x + m_padding.x, m_position.y + m_padding.y);
}

int Bar::Render()
{
	if (!m_isActive)
		return 0;

	if (0 <= m_backGroundImage.m_texture)
	{
		RECT frame{ 0, 0, g2_TextureWidth(m_backGroundImage.m_texture), g2_TextureHeight(m_backGroundImage.m_texture) };
		g2_Draw2D(m_backGroundImage.m_texture, &frame, &m_position, &m_backGroundImage.m_scaling);
	}

	if (0 <= m_fillAreaImage.m_texture && m_fillAmount > 0.0f)
	{
		RECT frame{ 0, 0, g2_TextureWidth(m_fillAreaImage.m_texture), g2_TextureHeight(m_fillAreaImage.m_texture) };
		g2_Draw2D(m_fillAreaImage.m_texture, &frame, &m_fillAreaPosition, &m_fillAreaScaling);
	}

	return 0;
}
