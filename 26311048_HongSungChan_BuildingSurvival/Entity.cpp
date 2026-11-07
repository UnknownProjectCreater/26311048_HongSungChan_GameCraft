#include "Entity.h"

int Entity::Update(float deltaTime)
{
	m_position += m_velocity * deltaTime;

	UpdateState(deltaTime);
	m_animator.Update(deltaTime);

	return 0;
}

int Entity::Render(Camera& camera)
{
	const RECT& frame = m_animator.CurrentFrame();
	if (IsRectEmpty(&frame))
		return -1;

	VEC2 screen = camera.WorldToScreen(this->GetPosition());

	g2_Draw2D(m_image.m_texture, &frame, &screen, &m_image.m_scaling);

	return 0;
}
